/**
 * Laborator 2
 */
package lab02;

/**
 * compararea două obiecte String vs șiruri de caractere
 */
public class TestDeEgalitate
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		String str1, str2;

		str1 = new String("Test de egalitate între șiruri.");
		str2 = str1;

		System.out.println("Șir1: " + str1);
		System.out.println("Șir2: " + str2);
		System.out.println("Același obiect? " + (str1 == str2));

		str2 = new String(str1);
		System.out.println("Șir1: " + str1);
		System.out.println("Șir2: " + str2);
		System.out.println("Același obiect? " + (str1 == str2));
		System.out.println("Același șir de caractere? " + str1.equals(str2));
	}
}
