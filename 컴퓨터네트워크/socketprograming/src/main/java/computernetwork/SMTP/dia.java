package computernetwork.SMTP;
import javax.swing.*;

public class dia extends JFrame{
	public dia() {
	      setLayout(null);
	      setSize(300,100);
	      JLabel good = new JLabel("메일 전송이 완료되었습니다! :D");
	      good.setSize(200,50);
	      good.setLocation(0,8);
	      good.setHorizontalAlignment(JLabel.CENTER);
	      add(good);
	      setVisible(true);
	      setLocation(500, 300);
	      setLocationRelativeTo(null);
	   }
}
