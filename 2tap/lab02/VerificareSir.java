/**
 * Laborator 2
 */
package lab02;

/**
 * operații simple cu clasa String
 */
public class VerificareSir
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		String str = "Oracle JDK nu este singura implementare Java!";

		System.out.println("Șirul este: " + str);
		System.out.println("Lungimea acestui șir: " + str.length());
		System.out.println("Caracterul din poziția 7: " + str.charAt(7));
		System.out.println("Subșirul de la 10 la 20: " + str.substring(10,20));
		System.out.println("Indexul caracterului 'u': " + str.indexOf('u'));
		System.out.println("Indexul de început al subșirului \"nu este\": " + str.indexOf("nu este"));
		System.out.println("Șirul scris cu litere mari: " + str.toUpperCase());
	}
}
