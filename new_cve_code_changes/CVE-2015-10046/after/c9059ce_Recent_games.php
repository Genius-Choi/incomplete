<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 

class Recent_games
{
	const NUM_GAMES_RETURN = 3;
	const LOL_GAMES = "games";
    const LOL_GAMEID = "gameId";
    const LOL_TEAM100 = "100";
    const LOL_TEAM200 = "200";
    const LOL_PLAYERS = "fellowPlayers";
    const LOL_SUMMONERID = "summonerId";
    const LOL_TEAMID = "teamId";
    const LOL_SUMMONERNAME = "name";
    const LOL_CHAMPIONSPRITE = "championSprite";
    const LOL_CHAMPIONID = "championId";
    const LOL_GAMEMODE = "gameMode";
    const LOL_CREATEDATE = "createDate";


  	private $CI;
    private $playerids;

	public function __construct()
    {
        $this->CI =& get_instance();
        $this->CI->load->library('lol_api');
        $this->CI->load->library('lol_image_formatter');
        $this->playerids = array();
    }

    public function get($id)
    {
    	//Check lol api
    	$recent_games = $this->CI->lol_api->get_recent_matches($id);
        $player_names = $this->get_player_names($recent_games, $id);
    	$games = array();
    	if(!empty($recent_games[self::LOL_GAMES]))
    	{
	    	for ($i=0; $i < self::NUM_GAMES_RETURN; $i++)
	    	{
	    		if(array_key_exists($i, $recent_games[self::LOL_GAMES])) 
                {
                    $games[$recent_games[self::LOL_GAMES][$i][self::LOL_GAMEID]] = $this->format($recent_games[self::LOL_GAMES][$i], $id, $player_names);    
                }
	    		
	    	}	
    	}
    	return $games;
    }

    private function format($game, $id, $player_names)
    {        
        $fellow_players = $game[self::LOL_PLAYERS];
        $time = unix_to_human($game[self::LOL_CREATEDATE]);
        
        //Add sign-in user first
        $formatted_game[$game[self::LOL_TEAMID]][0] =
                        array(self::LOL_SUMMONERID => $id,
                            self::LOL_CHAMPIONSPRITE => $this->CI->lol_image_formatter->get_champion_image($game[self::LOL_CHAMPIONID]),
                            self::LOL_SUMMONERNAME => $player_names[$id],
                            self::LOL_CHAMPIONID => $game[self::LOL_CHAMPIONID]
                            );

        foreach ($fellow_players as $player)
        {
            array_push($this->playerids, $player[self::LOL_SUMMONERID]);
            if($player[self::LOL_TEAMID] == self::LOL_TEAM100)
            {
                $num_elements = empty($formatted_game[self::LOL_TEAM100]) ? 0 : count($formatted_game[self::LOL_TEAM100]);
                $formatted_game[self::LOL_TEAM100][$num_elements] = 
                    array(self::LOL_SUMMONERID => $player[self::LOL_SUMMONERID],
                            self::LOL_CHAMPIONSPRITE => $this->CI->lol_image_formatter->get_champion_image($player[self::LOL_CHAMPIONID]),
                            self::LOL_SUMMONERNAME => $player_names[$player[self::LOL_SUMMONERID]],
                            self::LOL_CHAMPIONID => $player[self::LOL_CHAMPIONID]
                        );
            }
            else
            {
                $num_elements = empty($formatted_game[self::LOL_TEAM200]) ? 0 : count($formatted_game[self::LOL_TEAM200]);
                $formatted_game[self::LOL_TEAM200][$num_elements] = 
                    array(self::LOL_SUMMONERID => $player[self::LOL_SUMMONERID],
                            self::LOL_CHAMPIONSPRITE => $this->CI->lol_image_formatter->get_champion_image($player[self::LOL_CHAMPIONID]),
                            self::LOL_SUMMONERNAME => $player_names[$player[self::LOL_SUMMONERID]],
                            self::LOL_CHAMPIONID => $player[self::LOL_CHAMPIONID]
                        );
            }
        }
        //add time to game
        //TODO: get time zone
        $formatted_game['time'] = unix_to_human(substr($game[self::LOL_CREATEDATE], 0, -3));
        return $formatted_game;
    }

    private function get_player_names($games, $id)
    {
        $playerids = array();
        array_push($playerids, $id);
        for ($i=0; $i < self::NUM_GAMES_RETURN; $i++)
        {
            if($games != null && array_key_exists($i, $games[self::LOL_GAMES]))
            {
                $game = $games[self::LOL_GAMES][$i];
                foreach ($game[self::LOL_PLAYERS] as $player)
                {
                    array_push($playerids, $player[self::LOL_SUMMONERID]);
                }
            }
        }
        $summoner_names = $this->CI->lol_api->getSummoner(implode(",", $playerids), self::LOL_SUMMONERNAME);
        return $summoner_names;
    }
}