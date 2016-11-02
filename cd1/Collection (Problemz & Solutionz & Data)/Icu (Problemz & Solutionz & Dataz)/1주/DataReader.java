import java.io.*;
import java.util.StringTokenizer;

public class DataReader	{
	private StringTokenizer _string;
	
	public DataReader(String file_name)	{
		try	{
			FileReader reader = new FileReader(file_name);

			StringBuffer string = new StringBuffer();
			char[] buffer = new char[1024];
			int nRead;
			
			while ((nRead = reader.read(buffer)) != -1)
				string.append(new String(buffer, 0, nRead));
			
			reader.close();

			_string = new StringTokenizer(string.toString());
		} catch (IOException e)	{
			e.printStackTrace();
		}

	}

	public int readInt()	{
		return Integer.parseInt(_string.nextToken());
	}

	public String readString()	{
		return _string.nextToken();
	}
}
