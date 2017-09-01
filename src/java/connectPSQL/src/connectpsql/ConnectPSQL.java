/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package connectpsql;

import java.awt.FlowLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.WindowConstants;

class PasswordPanel extends JPanel {
  public final JPasswordField passwordField = new JPasswordField(12);
  private boolean gainedFocusBefore;

  /**
   * "Hook" method that causes the JPasswordField to request focus the first time this method is called.
   */
  void gainedFocus() {
    if (!gainedFocusBefore) {
      gainedFocusBefore = true;
      passwordField.requestFocusInWindow();
    }
  }

  public PasswordPanel() {
    super(new FlowLayout());

    add(new JLabel("Password: "));
    add(passwordField);
  }

  public char[] getPassword() {
      return passwordField.getPassword();
  }
}

public class ConnectPSQL {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
       /*
        Oppretter og initialiserer objekter av ulike SQL-relaterte klasser.
        */
        final PasswordPanel pnl = new PasswordPanel();
        JOptionPane op = new JOptionPane(pnl, JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        JDialog dlg = op.createDialog("Hvem der?");
        dlg.setVisible(true);
        dlg.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        /*dlg.addComponentListener(new ComponentListener() {

            @Override
            public void componentResized(ComponentEvent e) {
                System.out.println("dialog resized");
            }

            @Override
            public void componentMoved(ComponentEvent e) {
                System.out.println("dialog moved");
            }

            @Override
            public void componentShown(ComponentEvent e) {
                System.out.println("dialog shown");
            }

            @Override
            public void componentHidden(ComponentEvent e) {
                System.out.println("dialog hidden");
            }
        });*/
        dlg.addWindowFocusListener(new WindowAdapter() {
            /*@Override
            public void windowClosed(WindowEvent e)
            {
                System.out.println("jdialog window closed event received");
            }*/
            @Override
            public void windowGainedFocus(WindowEvent e){
                pnl.gainedFocus();
            }
        });
        Connection con = null;
        Statement st = null;
        PreparedStatement pst = null;
        ResultSet rs = null;
        String url = "jdbc:postgresql://localhost/mod_veritas";
        String user = "andersbo";
        if(op.getValue() != null && op.getValue().equals(JOptionPane.OK_OPTION))
        {
            dlg.dispose(); //dispose ser til at meldingsboksen faktisk blir lukket og ikke bare skjult.
            String password = new String(pnl.getPassword());
            try 
            {
                con = DriverManager.getConnection(url, user, password);
                st = con.createStatement();
                rs = st.executeQuery("SELECT VERSION()");
                if(rs.next())
                {
                    System.out.println(rs.getString(1));
                    JOptionPane.showMessageDialog(null, rs.getString(1), "PostgreSQL server versjon", JOptionPane.INFORMATION_MESSAGE);
                }
                rs = null;
                pst = con.prepareStatement("SELECT artsindeks, artnavn FROM art");
                rs = pst.executeQuery();
                while(rs.next())
                {
                    System.out.println(rs.getInt(1) + ": " + rs.getString(2));
                }
            } 
            catch (SQLException e) 
            {
                System.err.println(e.getMessage() + "\n\n\n" + e.toString());
            }
            finally
            {
                try
                {
                    if(rs != null)
                        rs.close();
                    if(st != null)
                        st.close();
                    if(con != null)
                        con.close();
                }
                catch(SQLException ex)
                {
                    System.err.println(ex.getMessage() + "\n\n\n" + ex.toString());
                }
            }
            System.out.println("Password enetered (not shown here).");
            dlg.removeAll();
            
            return;
        }
    }
}
