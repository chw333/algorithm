import java.io.*;
import java.util.*;

public class Matcher {

    protected static BufferedReader in = new BufferedReader( new InputStreamReader( System.in ) );

	public static void main( String args[ ] ) {
	
		String s, s1, s2;
		
		try { 
			while ( ( s = in.readLine( ) ) != null ) {
				StringTokenizer st = new StringTokenizer( s, " ", false );
				s1 = st.nextToken( );
				s2 = st.nextToken( );
				// System.out.println( s1 + "," + s2 );
				System.out.println( matches( s1, s2 ) );
			} // while String Pairs	
		} catch ( IOException e ) {
			e.printStackTrace( );
			System.exit( 1 );
		}
	} // main

	public static int matches( String a, String b ) {
	
		int myCount = 0;
		
		// System.out.println(a+","+b);

		// Beide am Ende, also Match vollstaendig:
		if ( a.length( ) == 0 && b.length( ) == 0 )
			return 1;

		// Anfang stimmt ueberein (inkl. +), also weiter-matchen:
		if ( a.length( ) > 0 && b.length( ) > 0
			 && ( a.charAt( 0 ) == b.charAt( 0 ) || b.charAt( 0 ) == '+' ) )
			myCount += matches( a.substring( 1 ), b.substring( 1 ) );
		
		// fuer * den 0 Match und den Head Match zählen
		if ( b.length( ) > 0 && b.startsWith( "*" ) ) {
			myCount += matches( a, b.substring( 1 ) );
			if ( a.length( ) > 0 )
				myCount += matches( a.substring( 1 ), b );
		}

		return myCount;

	} // matches
	
} // class Matches
