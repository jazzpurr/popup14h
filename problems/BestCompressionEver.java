
public class BestCompressionEver {
    /*Solved*/
	public static void main(String[] args) {
		new BestCompressionEver();
	}
	
	public BestCompressionEver(){
		Kattio kattio = new Kattio(System.in);
		long N = kattio.getLong(); //number of files of 1000 bits
		int b = kattio.getInt();
		String ans = solver(N, b);
		System.out.println(ans);
		kattio.close();
	}

	private String solver(long N, int b) {
		long maxCompressionNumber = 0;
		for(int i = 0; (i<=b) && (maxCompressionNumber<N); i++){
			maxCompressionNumber += 1L << i; 
		}
		if(maxCompressionNumber < N) return "no";
		else return "yes";
	}
}
