package computernetwork.SMTP;

import javax.swing.*;
import java.awt.*;
public class dia2 extends JFrame {
	public dia2(String text) {
		setLayout(null);
		setSize(320,120);
		JLabel failed1= new JLabel(text);
		failed1.setSize(300,30);
		failed1.setLocation(0,10);
		failed1.setHorizontalAlignment(JLabel.CENTER);
		add(failed1);
		JLabel failed2 = new JLabel("다시 확인해 주십시오.");
		failed2.setSize(300,30);
		failed2.setLocation(0,40);
		failed2.setHorizontalAlignment(JLabel.CENTER);
		add(failed2);
		setVisible(true);
		setLocation(500, 300);
		setLocationRelativeTo(null);
	}
}
