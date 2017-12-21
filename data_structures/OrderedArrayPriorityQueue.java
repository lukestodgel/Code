/**
 * cssc0956
 * 
 * Luke Stodgel
 */

package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class OrderedArrayPriorityQueue<E extends Comparable <E>> implements PriorityQueue<E> {
	
	private long modificationCounter;
	private int currentSize, maxSize;
	private E[] array;
	
	public OrderedArrayPriorityQueue(int max) {
		currentSize = 0;
		maxSize = max;
		modificationCounter = 0;
		array = (E[]) new Comparable[maxSize];	
		}
	
	public OrderedArrayPriorityQueue(){
		this(DEFAULT_MAX_CAPACITY);
	}
	
	//  Inserts a new object into the priority queue.  Returns true if
	//  the insertion is successful.  If the PQ is full, the insertion
	//  is aborted, and the method returns false.
	public boolean insert(E object) {
		if (isFull()) return false;
		
		int where = binSearch(object, 0, currentSize-1);
		for(int i = currentSize-1; i >= where; i--)
			array[i+1] = array[i];
		
		array[where] = object;
		currentSize++;
		modificationCounter++;
		return true;
	}

	//  Removes the object of highest priority that has been in the
	//  PQ the longest, and returns it.  Returns null if the PQ is empty.
	public E remove() {
		if(isEmpty()) return null;
		modificationCounter++;
		return array[--currentSize];
	}
	
	//  Returns the object of highest priority that has been in the
	//  PQ the longest, but does NOT remove it. 
	//  Returns null if the PQ is empty.
	public E peek() {
		if (isEmpty()) return null;
		return array[currentSize-1];
	}

	//  Returns true if the priority queue contains the specified element
	//  false otherwise.
	public boolean contains(E obj) {
		for(int i = 0; i < currentSize-1; i++) {
			if(array[i].compareTo(obj) == 0) return true;
		}
		return false;
	}

	//  Returns the number of objects currently in the PQ.
	public int size() {
		return currentSize;
	}
	
	//  Returns the PQ to an empty state.
	public void clear() {
		currentSize = 0;
		modificationCounter = 0;
	}

	//  Returns true if the PQ is empty, otherwise false
	public boolean isEmpty() {
		return currentSize == 0;
	}

	//  Returns true if the PQ is full, otherwise false.  List based
	//  implementations should always return false.
	public boolean isFull() {
		return currentSize >= maxSize;
	}

	public int binSearch(E obj, int lo, int hi) {
		if(hi < lo) return lo;
		int mid = (lo+hi) >> 1;
		int c = obj.compareTo(array[mid]);
		if(c>=0) return binSearch(obj, lo, mid-1); //go left
		return binSearch(obj, mid+1, hi); //go right
	}

	class IteratorHelper implements Iterator<E> {
		int index;
		long modCheck;
		
		public IteratorHelper() {
			index = 0;
			modCheck = modificationCounter;
		}
		
		public boolean hasNext() {
			if(modCheck == modificationCounter)
				return index < currentSize;
			throw new ConcurrentModificationException();
		}
		
		public E next() {
			if(!hasNext()) throw new NoSuchElementException();
			return array[index++];
		}
		
	}
	//  Returns an iterator of the objects in the PQ, in no particular
	//  order.  The iterator must be fail-fast.
	public Iterator<E> iterator() {
		return new IteratorHelper();
	}

} 