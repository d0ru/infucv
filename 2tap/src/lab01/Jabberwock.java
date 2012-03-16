/**
 * Laborator 1
 */
package lab01;

/**
 * Realizarea unui clase Jabberwock (dragon imaginat de Lewis Carroll)
 *
 * Atribute Jabberwock
 * - Culoare: portocaliu, pamântiu, galben lămâie, galben aprins
 * - Sex: masculin, feminin, nu e treaba ta
 * - Pofta: sătul, flămând
 */
public class Jabberwock
{
	String culoare;
	String sex;
	boolean flamand;

	// O metodă care să-i definească comportamentul
	void hranescJabberwock()
	{
		if (true == flamand) {
			System.out.println("Bun, un Jabberwock flamand!");
			flamand = false;
		} else {
			System.out.println("Nu, multumesc - am mancat deja!");
		}
	}

	// O alta metodă de afişare a atributelor
	void afisareAtribute()
	{
		System.out.println("I: acesta este un jabberwock " + sex + " " + culoare + ".");
		if (flamand == true)
			System.out.println("Jabberwock-ul este flamand");
		else
			System.out.println("Jabberwock-ul este satul");
	}

	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		Jabberwock j = new Jabberwock();

		j.culoare = "portocaliu";
		j.sex = "mascul";
		j.flamand = true;
		System.out.println("Apelez afisareAtribute ...");
		j.afisareAtribute();

		System.out.println("\nHranesc Jabberwock-ul ...");
		j.hranescJabberwock();
		System.out.println("\nApelez afisareAtribute ...");
		j.afisareAtribute();

		System.out.println("\nHranesc Jabberwock-ul ...");
		j.hranescJabberwock();
	}
}
