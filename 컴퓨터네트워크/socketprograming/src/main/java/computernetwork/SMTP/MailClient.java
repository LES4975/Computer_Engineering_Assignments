package computernetwork.SMTP;

import java.awt.*;
import java.awt.event.*;
import java.net.SocketException;
import javax.swing.*;

public class MailClient extends JFrame{
   JLabel recipientf = new JLabel("받는 사람");
   JTextField recipientb= new JTextField();
   JLabel subjectf = new JLabel("제목");
   JTextField subjectb = new JTextField();
   JLabel contentf = new JLabel("내용");
   JTextArea contentb = new JTextArea();
   
   public MailClient() {
      setTitle("컴퓨터 네트워크 프로젝트 1 메일 전송 클라이언트");
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      Container c= getContentPane();
      c.setLayout(null);
      
      
      recipientf.setLocation(20,20);
      recipientf.setSize(60,30);
      c.add(recipientf);
      
      recipientb.setLocation(100,20);
      recipientb.setSize(350,30);
      c.add(recipientb);
      
      
      subjectf.setLocation(20,60);
      subjectf.setSize(80,30);
      c.add(subjectf);
      
      subjectb.setLocation(100,60);
      subjectb.setSize(350,30);
      c.add(subjectb);
      
      
      contentf.setLocation(20,100);
      contentf.setSize(50,30);
      c.add(contentf);
      
      contentb.setLocation(100,100);
      contentb.setSize(450,250);
      contentb.setLineWrap(true);
      c.add(contentb);
      
      JButton sendingbutton = new JButton("전송");
      sendingbutton.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent e) {
            
            try{
               if(recipientb.getText().equals("")) {
                  
                  
                  new dia2("수신자의 성함이 올바르지 않습니다. :(");
                  return;
                  
               }
               else if(subjectb.getText().equals("")) {
                  
                  new dia2("제목을 적어주십시오. :(");
                  return;
                  
               }
               else {
                  MailServer.sendMail(recipientb.getText(),subjectb.getText(),contentb.getText());
                  
                  recipientb.setText("");
                  subjectb.setText("");
                  contentb.setText("");
               }
               }
            
            catch(Exception ex) {
               System.out.println("Something is wrong");
               return;
            }
         }
      });
      sendingbutton.setLocation(470,30);
      sendingbutton.setSize(80,50);
      c.add(sendingbutton);
      
      setSize(600,410);
      setLocationRelativeTo(null);
      setVisible(true);
      
   }
}