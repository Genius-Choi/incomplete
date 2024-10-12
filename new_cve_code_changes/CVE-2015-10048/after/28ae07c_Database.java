package com.dextra.injectit.database;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import sun.security.provider.ConfigFile.Spi;

public class Database {

	private Database() {
	}

	private static Connection getConnection() {
		try {
			return DriverManager.getConnection("jdbc:hsqldb:mem:.", "SA", "");
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	public static ResultSet executeStoredPrcedure(String spCalled, Object... parameters){
		Connection conn = getConnection();
		CallableStatement cs = null;

		try {
			cs = conn.prepareCall(spCalled);
			if (parameters != null)
				for (int parameterIndex = 0; parameterIndex < parameters.length; ++parameterIndex){
					cs.setObject(parameterIndex + 1, parameters[parameterIndex]);
				}
			System.out.println(cs.toString());
			if (cs.execute())
				return  cs.executeQuery();	
			else 
				return null;
		} catch (SQLException e) {
		
			throw new RuntimeException(e);
		
		} finally {
			try {
				if (cs != null) {
					cs.close();
				}
				conn.close();
			} catch (SQLException e) {
				throw new RuntimeException(e);
			}
		}
	}
	
	public static ResultSet execute(String sql, Object... objects) {
		Connection conn = getConnection();
		PreparedStatement ps = null;
		
		try {
			System.out.println(sql);
			ps = conn.prepareStatement(sql);
			
			// Set the parameters
			if (objects != null)
				for (int parameterIndex = 0; parameterIndex < objects.length; ++parameterIndex){
					ps.setObject(parameterIndex + 1, objects[parameterIndex]);
				}
			
			if (ps.execute())
				return ps.getResultSet();
			else
				return null;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new RuntimeException(e);
		} finally {
			try {
				if (ps != null) {
					ps.close();
				}
				conn.close();
			} catch (SQLException e) {
				throw new RuntimeException(e);
			}
		}
	}

}
