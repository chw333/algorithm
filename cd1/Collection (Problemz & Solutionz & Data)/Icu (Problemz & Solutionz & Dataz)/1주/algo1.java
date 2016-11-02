import java.io.*;

public class algo1	{	
	public static void main(String[] args)	{
		int[] stack1 = new int[256];
		int[] stack2= new int[256];
		int[] outpt= new int[256];
				

		int n, train[];
		int count=1;
		int st1, st2=0;
		int i;
		int ooo=0;

		DataReader reader = new DataReader("input.txt");
		n = reader.readInt();
		st1=n;
		train = new int[n];
		for (i=0; i<n; i++)	{
			train[i] = reader.readInt();
/*			System.out.print(train[i]);*/

		}
		count=0;
		st1=n;
		st2=0;
		for (i=1;i<=n;i++) stack1[i]=n-i+1;
		for(;;){
			if (stack2[st2]==train[count]) {
				outpt[++ooo]=1;
				count++;
				st2--;
			}
			else {
				if (st1==0) {ooo=-1; break; }
				stack2[++st2]=stack1[st1];
				outpt[++ooo]=2;
				stack1[st1]=0;
				st1--;
			}
			if (count>=n) break;

		}		
		
		
		try	{
			FileWriter writer = new FileWriter("output.txt");
			if (ooo==-1) {writer.write("IMPOSSIBLE"); }
			else {
				for (i=1;i<=ooo;i++) {
					if (outpt[i]==1) writer.write("X");
					if (outpt[i]==2) writer.write("S");
				}
			}
			writer.close();
		} catch (IOException e)	{
			e.printStackTrace();
		}
	}
}
