<?php
    /**
     * USe for testing Code
     * php version 8.1
     *
     * @category Test
     *
     * @package None
     *
     * @author Waqas <waqaskanju@gmail.com>
     *
     * @license http://www.waqaskanju.com/license MIT
     *
     * @link http://www.waqaskanju.com/
     **/

require_once 'sand_box.php';
$link=$LINK;



echo $query = 'SELECT Name,Class FROM students_info WHERE Name=? AND Class=?';
$result = mysqli_execute_query($link, $query, ['Abdullah','5th']);
foreach ($result as $row) {
    printf($row["Name"]. $row['Class']);
    echo "<br>";
}
?>
