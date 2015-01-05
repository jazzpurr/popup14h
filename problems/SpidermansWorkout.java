
public class SpidermansWorkout {

	public class Struct {
		int maxValue;
		int prev;

		public Struct(int maxValue, int prev){
			this.maxValue = maxValue;
			this.prev = prev;
		}
	}

	private int[] moves;
	private Struct[][] matrix;
	private int maxHeight;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new SpidermansWorkout();
	}

	public SpidermansWorkout(){
		Kattio kattio = new Kattio(System.in);
		//		Kattio kattio = new Kattio("src\\new0.txt");
		int nuoTestCases = kattio.getInt();
		int nuoMoves;
		for(int i = 0; i < nuoTestCases; i++){
			nuoMoves = kattio.getInt();
			moves = new int[nuoMoves];
			for(int j = 0; j < nuoMoves; j++){
				moves[j] = kattio.getInt();
			}
			System.out.println(solver());
		}
		kattio.close();
	}

	private String solver() {
		maxHeight = findMaxHeight(moves);
		if(maxHeight < 0) return "IMPOSSIBLE";
		matrix = new Struct[maxHeight+1][moves.length];
		matrixFiller(0, 0, 0);
		//		for(int i = maxHeight; i >= 0; i--){
		//			for(int j = 0; j < moves.length; j++){
		//				System.out.print(matrix[i][j] + " ");
		//			}
		//			System.out.println();
		//		}
		return outputter();
	}

	private void matrixFiller(int prevHeight, int currStep, int prevMax) {
		if(currStep < moves.length){
			int newHeight1 = prevHeight + moves[currStep];
			int newHeight2 = prevHeight - moves[currStep];
			if(newHeight1 <= maxHeight){
				int newMax = Math.max(newHeight1, prevMax);
				if(matrix[newHeight1][currStep] == null){
					matrix[newHeight1][currStep] = new Struct(newMax, prevHeight);
					matrixFiller(newHeight1, currStep+1, newMax);
				}
				else{
					if(matrix[newHeight1][currStep].maxValue > newMax){
						matrix[newHeight1][currStep] = new Struct(newMax, prevHeight);
						matrixFiller(newHeight1, currStep+1, newMax);
					}
				}
			}
			if(newHeight2 >= 0){
				if(matrix[newHeight2][currStep] == null){
					matrix[newHeight2][currStep] = new Struct(prevMax, prevHeight);
					matrixFiller(newHeight2, currStep+1, prevMax);
				}
				else{
					if(matrix[newHeight2][currStep].maxValue > prevMax){
						matrix[newHeight2][currStep] = new Struct(prevMax, prevHeight);
						matrixFiller(newHeight2, currStep+1, prevMax);
					}
				}
			}
		}
	}

	private int findMaxHeight(int[] moves){
		int sum = 0;
		for(int i = 0; i < moves.length; i++){
			if(moves[i] > 500) return -1; //impossible, too large
			sum += moves[i];
		}
		if((sum % 2 != 0) || (sum > 1000)) return -1; //impossible, uneven or too large
		int result = sum/2;
		return result;
	}

	private String outputter() {
		StringBuilder sb = new StringBuilder();
		if(matrix[0][moves.length-1] == null){
			return "IMPOSSIBLE";
		}
		else{ //backtrack
			int currPos = 0; // we end at 0
			int prevPos = matrix[0][moves.length-1].prev;
			for(int i = moves.length-1; i>=1; i--){
				if(prevPos > currPos){
					sb.append("D");
				}
				else{
					sb.append("U");
				}
				currPos = prevPos;
				prevPos = matrix[prevPos][i-1].prev;
			}
			sb.append("U");
			sb.reverse();
			return sb.toString();
		}
	}
}

