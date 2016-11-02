import java.awt.*;
import java.awt.event.*;

public class game3 {
	public static void main(String[] args) {
		Frame hhh = new Frame("Creat Window Test");
		hhh.setSize(300,200);
		hhh.setVisible(true);

		hhh.addWindowListener(new WindowCloser());
	}
}

class WindowCloser extends WindowAdapter	{
	public void windowClosing(WindowEvent e)	{
		System.exit(0);
	}
}