package com.dextra.injectit.servlets;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.dextra.injectit.database.Database;
import com.dextra.injectit.database.User;
import com.google.gson.Gson;

public class InjectServlet extends HttpServlet {

	private static final long serialVersionUID = 1267446324696819053L;

	//@Override
	protected void doGet2(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		resp.setContentType("application/json");
		resp.setCharacterEncoding("utf8");
		resp.setStatus(200);
		
		ServletOutputStream os = resp.getOutputStream();
		os.print("[");
		os.print("{\"name\":\"Moretinho\",\"password\":\"eumeamo\",\"creditCardNumber\":\"38386633\"}");
//		os.print(new Gson().toJson(new User("Moretinho", "eumeamo", "38386633")));
		os.print("]");
		os.flush();
		os.close();
//		try {
//			String query = "SELECT * FROM USER";
//			
//			ResultSet rs = Database.execute(query);
//			resp.setContentType("text/html");
//			ServletOutputStream os = resp.getOutputStream();
//			os.print("<table>");
//			os.print("<thead><th>Nome</th><th>Senha</th><th>Cart&atilde;o</th></thead>");
//			os.print("<tbody>");
//
//			rs.first();
//			while (rs.next()) {
//				os.print(String.format(
//						"<tr><td>%s</td><td>%s</td><td>%s</td></tr>",
//						rs.getString(1), rs.getString(2), rs.getString(3)));
//			}
//
//			os.print("</tbody>");
//			os.print("</table>");
//
//			os.flush();
//			os.close();
//		} catch (SQLException e1) {
//			throw new ServletException(e1.getMessage());
//		}
	}
	
	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		// Nome dos usuario pesquisado
		String name = req.getParameter("name");
		
		String query = "SELECT * FROM USER WHERE NAME = '" + name + "'";
		ResultSet users = Database.execute(query);
		
		ArrayList<User> searchedUsers = new ArrayList<User>();
		try {
			
			while (users.next()){
				searchedUsers.add(new User(users.getString(1),users.getString(2),users.getString(3)));
			}
			
			Gson gson = new Gson();
			ServletOutputStream os = resp.getOutputStream();
			
			os.print(gson.toJson(searchedUsers));
			os.flush();
			os.close();

		} catch (SQLException e) {
			e.printStackTrace();
		}	
		
	}
	
	public static void main(String[] args) {
		/////////////////
		// TESTE DE SQL INJECTION
		
		
		String query = "SELECT * FROM USER WHERE NAME = ?";
		ResultSet users = Database.execute(query);
		
		ArrayList<User> searchedUsers = new ArrayList<User>();
		try {
			
			while (users.next()){
				searchedUsers.add(new User(users.getString(1),users.getString(2),users.getString(3)));
			}
			
			Gson gson = new Gson();
			System.out.println(gson.toJson(searchedUsers));

		} catch (SQLException e) {
			e.printStackTrace();
		}	
	}
}
