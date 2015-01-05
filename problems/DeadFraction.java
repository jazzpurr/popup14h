public class DeadFraction {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new DeadFraction();
	}

	public DeadFraction(){
		Kattio kattio = new Kattio(System.in);
//		Kattio kattio = new Kattio("src\\new0.txt");
		String input = kattio.getWord();
		while(!input.equals("0")){
			input = input.substring(2, input.length()-3);   //0. -this- ...
			System.out.println(solver(input));
			input = kattio.getWord();
		}
		kattio.close();
	}

	private String solver(String input) {
		//Divide into two parts, non-periodic and periodic.
		int inputAsInt = Integer.parseInt(input);
		long minDenominator = Long.MAX_VALUE;
		long minNumerator = 0;
		long denominator, numerator, gcd, partOneAsInt;
		String partOne;
		long[] tenToThePowerOfArray = new long[input.length()+1];
		tenToThePowerOfArray[0] = 1;
		for(int i = 1; i < tenToThePowerOfArray.length; i++){
			tenToThePowerOfArray[i] = tenToThePowerOfArray[i-1]*10;
		}
		for(int i = 1; i <= input.length(); i++){
			partOne = input.substring(0, input.length() - i);
			if(partOne.length() > 0){ 
				partOneAsInt = Integer.parseInt(partOne);
			}
			else{
				partOneAsInt = 0;
			}
			denominator = tenToThePowerOfArray[input.length()]-tenToThePowerOfArray[input.length()-i];
			numerator = inputAsInt - partOneAsInt;
			gcd = gcd(denominator, numerator);
			denominator /= gcd;
			numerator /= gcd;
			if(minDenominator > denominator){
				minDenominator = denominator;
				minNumerator = numerator;
			}
		}
		return minNumerator + "/" + minDenominator;
	}
	
	public long gcd(long a, long b) {
		   if (b==0) return a;
		   return gcd(b,a%b);
		}
	
}