import java.awt.*;
import java.awt.event.*;

public class game2 extends Frame{
	Canvas canvas;
	public static void main(String[] args) {
		Frame hhh = new Frame("Creat Window Test");
		hhh.setSize(300,200);
		hhh.setVisible(true);
		
		new game2();
		
		hhh.addWindowListener(new WindowCloser());
	}
	public game2() {
		super("game2");
		canvas = new Canvas();
		canvas.setSize(200,100);
		add("test.gif", canvas);
		setVisible(true);
		return;
	}
}

class WindowCloser extends WindowAdapter	{
	public void windowClosing(WindowEvent e)	{
		System.exit(0);
	}
}