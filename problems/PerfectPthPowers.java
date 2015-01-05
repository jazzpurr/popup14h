public class PerfectPthPowers {
    private int[] primes;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new PerfectPthPowers();
	}

	public PerfectPthPowers(){
		SmallestPrimes sp = new SmallestPrimes();
		primes = sp.getPrimes(); //5000 first primes. 5000th prime ^2 > maxint.
		
		Kattio kattio = new Kattio(System.in);
//		Kattio kattio = new Kattio("src\\new0.txt");
		int input = kattio.getInt();
		while(input != 0){
			System.out.println(solver(input));
			input = kattio.getInt();
		}
		kattio.close();
	}

	private String solver(int input) {
		int tmpP = 0;
		int realP = 0;
		for(int i = 0; i < primes.length; i++){
			if(input%primes[i] == 0){
				tmpP = 0;
				while(input%primes[i] == 0){
					input = input / primes[i];
					tmpP++;
				}
				if(realP == 0){
					realP = tmpP;
				}
				else{
					if(realP != tmpP){ //not a match, find GCD of the two
						realP = gcd(realP, tmpP);
					}
				}
			}
		}
		if(realP == 0){ //p can only be one
			realP = 1; 
		}
		if(input<0){
            while(realP%2 == 0){ //all two-divisions must be unmade
            	realP /= 2; //divide by two 
            }
        }
		
		return realP + "";
	}
	
	public int gcd(int a, int b) {
		   if (b==0) return a;
		   return gcd(b,a%b);
		}
	
}
