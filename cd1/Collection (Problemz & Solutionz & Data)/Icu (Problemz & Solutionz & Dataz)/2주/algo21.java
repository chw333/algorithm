import java.io.*;

public class algo21	{	
	public static void main(String[] args)	{
		int q,w,e;
		int n, loop, check;
		int ttemp;
		int ok=0;
		int[] a = new int[256];
		int[] b = new int[256];

		int sol=0; 
		int[][] ans = new int[256][];
		for (int i=0; i<256; i++)
			ans[i] = new int[100];


		DataReader reader = new DataReader("input.txt");
		n = reader.readInt();
		for (q=1;q<=n;q++){
			a[q]= reader.readInt();
		}
		loop = reader.readInt();
		for (q=1;q<=loop;q++){
			
			for (w=1;w<=n;w++){
				b[w]=reader.readInt();
			}
			ok=0;
			for (w=1;w<=n;w++){
				check=0;
				for (e=1;e<=n;e++){
					if (a[e]!=b[(w+e-1)%n+1]) {check=1;

					break; }
				}
				if (check==0) {
				sol++;ok=1;
				for (e=1;e<=n;e++){
					ans[sol][e]=b[e];
				}
				break; }
			}
			if (ok==1) continue;
			for (w=1;w<=n;w++){
				check=0;
				for (e=1;e<=n;e++){

					if (((a[e]+1)%4+1)!=b[(n+1)-((w+e-1)%n+1)]) {check=1;

					break; }
				}
				if (check==0) {
				sol++;
				for (e=1;e<=n;e++){
					ans[sol][e]=b[e];
				}
				break; }
			}
//			break;
		}
		
		
		try	{
			FileWriter writer = new FileWriter("output.txt");
			writer.write(sol+'0');
			writer.write('\n');
			for (q=1;q<=sol;q++){
				for (w=1;w<=n;w++){
					writer.write(ans[q][w]+'0');
				}
			writer.write('\n');
			}

			writer.close();
			} catch (IOException ee)	{
			ee.printStackTrace();
		}
	}
}
