
public class Ladder {
		/**
		 * @param args
		 */
		public static void main(String[] args) {
			new Ladder();
		}
		
		public Ladder(){
			Kattio kattio = new Kattio(System.in);
//			Kattio kattio = new Kattio("src\\new0.txt");
			double height = kattio.getInt();
			double angle = kattio.getInt();
			System.out.println(solver(height, angle));
			
			kattio.close();
		}

		private String solver(double height, double angle) {
			double hypotenuse = height / Math.sin(Math.toRadians(angle));
			int retVal = (int) Math.ceil(hypotenuse);
			return retVal + "";
		}
}
