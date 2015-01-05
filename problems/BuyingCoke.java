
public class BuyingCoke {

	/**
	 * Unsolved, correct on test cases, wrong in Kattis.
	 */
	public static void main(String[] args) {
		new BuyingCoke();
	}
	
	public BuyingCoke(){
		Kattio kattio = new Kattio(System.in);
		int nuoTestCases = kattio.getInt();
		int c, n1, n5, n10;
		for(int i = 0; i < nuoTestCases; i++){
			c = kattio.getInt();
			n1 = kattio.getInt();
			n5 = kattio.getInt();
			n10 = kattio.getInt();
			solver(c, n1, n5, n10);
		}
		kattio.close();
	}

	private void solver(int c, int n1, int n5, int n10) {
    	int nuoInputCoins = 0;
		for(int i = c; i > 0; i--){
			if((n10+n5 >= i) && (n10 >= 1)){
				n10 -= 1;
				n1 += 2;
				nuoInputCoins += 1;
			}
			else if((n10 >= 1) && (n1 >= 3)){
				n10 -= 1;
				n1 -= 3;
				n5 += 1;
				nuoInputCoins += 4;
			}
			else if((n5 > i) && (n5 >= 2)){
				n5 -= 2;
				n1 += 2;
				nuoInputCoins += 2;
			}
			else if((n5 >= 1) && (n1 >= 3)){
				n5 -= 1;
				n1 -= 3;
				nuoInputCoins += 4;
			}
			else if(n1 >= 8){
				n1 -= 8;
				nuoInputCoins += 8;
			}
			else{
				System.out.println("Insufficient Funds");
			}
		}
		System.out.println(nuoInputCoins);
	}

}
