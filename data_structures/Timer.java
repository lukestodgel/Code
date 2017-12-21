package data_structures;

/*  Timer.java
A sample class to assist in performing empirical timing tests
for your project #2.    

This timer includes only add/delete cycle times.
The structure size is not doubled each time, but increases in a 
linear fashion.

If it takes too long on your machine, reduce structureSize and 
increment.  Note that both vars must have same value.

CS310 Spring 2017
Alan Riggins
*/    


public class Timer {
public static void main(String [] args) {
	new Timer();
}
public Timer() {
    int iterations = 20;  // number of timing tests
    int workSize = 10000;   // size of add/remove cycle loop
    int structureSize = 10000;  // initial size of PQ
    int increment = 10000; // make this the same size as structureSize        
    int loopStructureSize = structureSize; // helper var


    long start = 0, stop = 0;

                    
    PriorityQueue<Integer> pq = 
            new OrderedArrayPriorityQueue<Integer>(512000);
           // new UnorderedArrayPriorityQueue<Integer>(512000);
         //   new OrderedListPriorityQueue<Integer>();
          //  new UnorderedListPriorityQueue<Integer>();                                                
    
    
    for(int i=0; i < iterations; i++) {
        // build structure first            
 
        for(int j=0; j < increment; j++) {
            int x = (int) (Integer.MAX_VALUE * Math.random());
            pq.insert(x);
            }
                            
        // time for add/remove cycles   
        start = System.currentTimeMillis();  
        for(int j=0; j < workSize; j++) {
            int x = (int) (Integer.MAX_VALUE * Math.random());
            pq.insert(x);            
            pq.remove();
            }
        stop = System.currentTimeMillis();
        System.out.println("n=" + pq.size() + "  Time: " + (stop-start));
                 
        structureSize += increment;
        }                                         
    }
}
