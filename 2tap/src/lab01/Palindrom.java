/**
 * Laborator 1
 */
package lab01;

import java.applet.Applet;
import java.awt.*;

/**
 * Toate applet-urile reprezintă subclase ale clasei "Applet".
 * Toate applet-urile trebuie declarate "public".
 */
public class Palindrom extends Applet
{
	private static final long serialVersionUID = -763528173069653518L;
	Font f = new Font ("TimesRoman", Font.BOLD, 36);

	/**
	 * O metodă publică nu poate fi suprascrisă decât de o metodă publică.
	 */
	public void paint (Graphics ecran)
	{
		ecran.setFont(f);
		ecran.setColor(Color.red);
		ecran.drawString("Primul applet în Java!", 20, 60);
	}
}
