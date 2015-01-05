import java.util.ArrayList;


public class IgnoreTheGarbage {

    /**
	 * @param args
	 */
	public static void main(String[] args) {
		new IgnoreTheGarbage();
	}

	public IgnoreTheGarbage(){
					Kattio kattio = new Kattio(System.in);
//		Kattio kattio = new Kattio("src\\new0.txt");
		ArrayList<Integer> kList = new ArrayList<Integer>();
		String input = kattio.getWord();
		while(input != null){
			kList.add(Integer.parseInt(input));
			input = kattio.getWord();
		}
		solver(kList);
		kattio.close();
	}
	
	private void solver(ArrayList<Integer> kList) {
		int[] compValues = new int[]{0, 1, 2, 5, 9, 8, 6};
		int[] increments = new int[]{1, 7, 49, 343, 2401, 16807, 117649, 823543, 5764801, 40353607, 282475249, 1977326743};
		long[] incrementsRep = new long[]{1L, 10L, 100L, 1000L, 10000L, 100000L, 1000000L, 10000000L, 100000000L, 1000000000L, 10000000000L, 100000000000L};
		int[] incrementsUsage;
		int k;
		long value;
		StringBuilder sb;
		for(int i = 0; i < kList.size(); i++){
			k = kList.get(i);
			incrementsUsage = new int[increments.length];
			for(int j = increments.length-1; j >= 0; j--){
				while(k >= increments[j]){
					k -= increments[j];
					incrementsUsage[j]++;
				}
			}
			
			value = 0;
			for(int j = 0; j < incrementsUsage.length; j++){
				value += compValues[incrementsUsage[j]] * incrementsRep[j];
			}
			sb = new StringBuilder(value + "");
			sb.reverse();
			System.out.println(sb.toString());
		}
	}

	private void naiveSolver(ArrayList<Integer> kList) {
		int maxIndex = 0;
		for(int i:kList){
			if(i > maxIndex){
				maxIndex = i;
			}
		}
		String[] ansList = createAnswerList(maxIndex);
		int k;
		for(int i = 0; i < kList.size(); i++){
			k = kList.get(i);
			System.out.println(ansList[k-1]);
		}
	}

	private String[] createAnswerList(int maxIndex) {
		String[] ansList = new String[maxIndex];
		boolean nextFound = false;
		int x = 1;
		String xStr;
		StringBuilder xSB;
		for(int i = 0; i < maxIndex; i++){
			while(!nextFound){
				xStr = x + "";
				if(!xStr.contains("3") && !xStr.contains("4") && !xStr.contains("7")){ //valid
					nextFound = true;
					xStr = xStr.replace('6','t');
					xStr = xStr.replace('9','6');
					xStr = xStr.replace('t','9');
					xSB = new StringBuilder(xStr);
					xSB.reverse();
					ansList[i] = xSB.toString();
				}
				x++;
			}
			nextFound = false;
		}
		return ansList;
	}


}
