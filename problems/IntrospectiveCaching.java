import java.util.PriorityQueue;
import java.util.Comparator;

public class IntrospectiveCaching {

    /*Solved*/
	private int[] accesses;
	private int maxCacheSize;
	private int systemSize;

	/**
	 * @param args
	 */

	/*Solved*/
	public class Struct {
		int index;
		int target;

		public Struct(int index, int target){
			this.index = index;
			this.target = target;
		}
	}
	public class StructComparator implements Comparator<Struct>{
		@Override
		public int compare(Struct x, Struct y){
			if (x.target > y.target) {
				return -1;
			}
			else if (x.target == y.target) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
	public static void main(String[] args) {
		new IntrospectiveCaching();
	}

	public IntrospectiveCaching(){
						Kattio kattio = new Kattio(System.in);
//		Kattio kattio = new Kattio("src\\new0.txt");
		maxCacheSize = kattio.getInt();
		systemSize = kattio.getInt();
		accesses = new int[kattio.getInt()];
		for(int i = 0; i < accesses.length; i++){
			accesses[i] = kattio.getInt();
		}
		System.out.println(solver());
		kattio.close();
	}

	private String solver() {
		int[] nextConstructor = new int[systemSize];
		int[] nextAppearance = new int[accesses.length];
		boolean[] inCache = new boolean[systemSize];
		
		//constructor
		for(int i = 0; i < systemSize; i++){
			nextConstructor[i] = Integer.MAX_VALUE;
		}
		
		//next
		for(int i = accesses.length-1; i >= 0; i--){
			nextAppearance[i] = nextConstructor[accesses[i]];
			nextConstructor[accesses[i]] = i;
		}

		
		// solver
		Comparator<Struct> comparator = new StructComparator();
    	PriorityQueue<Struct> pQ = new PriorityQueue<Struct>(maxCacheSize, comparator);
		int cacheEdits = 0;
		int currCacheUsage = 0;
		int currTarget;
		for(int i = 0; i < accesses.length; i++){
			currTarget = accesses[i];
			
			if(!inCache[currTarget]){
				inCache[currTarget] = true;
				cacheEdits++;
				
				if(currCacheUsage < maxCacheSize){
					currCacheUsage++;
				}
				else {
					Struct toRemove = pQ.poll();
					inCache[toRemove.index] = false;
				}
			}
			pQ.add(new Struct(currTarget, nextAppearance[i]));
		}
		return cacheEdits + "";
	}
}
	
