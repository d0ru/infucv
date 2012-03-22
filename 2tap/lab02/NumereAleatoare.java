/**
 * Laborator 2
 */
package lab02;

import java.util.Random;

/**
 * creează obiecte folosite pentru generarea de numere aleatoare
 */
public class NumereAleatoare
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		Random r1,r2;

		// depinde de ora la care se rulează programul
		r1 = new Random();
		System.out.println("Valoarea aleatoare 1: " + r1.nextDouble());

		// valoarea trebuie să fie întotdeauna aceeaşi
		r2 = new Random(8675309);
		System.out.println("Valoarea aleatoare 2: " + r2.nextDouble());
	}
}
