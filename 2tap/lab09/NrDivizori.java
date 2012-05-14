package lab09;

import java.util.Scanner;

/**
 * Program care caută un întreg din intervalul [1, 10000] cu cel mai mare număr de divizori.
 * Numărul de fire de execuție este cerut interactiv.
 */
public class NrDivizori extends Thread {
	final static int MAXIM = 10000;
	int prim;
	int ultim;
	int nr;		// numărul cu cel mai mulți divizori
	int max;	// numărul maxim de divizori

	NrDivizori(int prim, int ultim) {
		this.prim = prim;
		this.ultim = ultim;
	}

	public void run() {
		int i, d;
		
		this.nr = this.prim;
		this.max = 1;
		for (i = this.prim; i <= this.ultim; ++i) {
			d = nrdiv(i);
			if (d > this.max) {
				this.max = d;
				this.nr = i;
			}
		}
	}

	static int nrdiv(int x) {
		int i, j, n;
		
		j = x / 2;
		n = 1;
		if (0 == x % 2)
			for (i = 2; i <= j; i += 2)
				if (0 == x % i)
					++n;
		for (i = 3; i <= j; i += 2)
			if (0 == x % i)
				++n;
		return n;
	}

	public static void main(String[] args) {
		int i, nrfire, p, u, k, max;
		long tstart, tstop;
		Scanner in = new Scanner(System.in);
		
		System.out.print("Câte fire de execuție dorești: ");
		nrfire = in.nextInt();
		NrDivizori[] fire = new NrDivizori[nrfire];
		assert(nrfire == fire.length);
		
		k = MAXIM / nrfire;
		p = 1;
		u = k;
		for (i = 0; i < fire.length; ++i, p += k) {
			fire[i] = new NrDivizori(p, u);
			u += k;
			if (u > MAXIM)
				u = MAXIM;
		}
		
		tstart = System.currentTimeMillis();
		for (i = 0; i < fire.length; ++i)
			fire[i].start();

		for (i = 0; i < fire.length; ++i) {
			try {
				fire[i].join();
			} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			}
		}
		tstop = System.currentTimeMillis();
		
		k = 0;
		max = fire[0].max;
		for (i = 1; i < fire.length; ++i)
			if (fire[i].max > max) {
				k = i;
				max = fire[i].max; 
			}
		System.out.println("Nr. «" + fire[k].nr + "» are cel mai mare număr de divizori (" + fire[k].max + ").");
		System.out.println("Timpul de execuție: " + (tstop - tstart) / 1000.0);
	}
}
