/**
 * cssc0956
 * 
 * Luke Stodgel
 */


package data_structures;
 
import java.util.Iterator;
import java.util.NoSuchElementException;

public class UnorderedList<E extends Comparable <E>> implements PriorityQueue<E> {
	
    public static final int DEFAULT_MAX_CAPACITY = 1000;
    private int currentSize;
    Node<E> head, tail;
    
    public UnorderedList() {
    	head = tail = null;
    	currentSize = 0;
    }
    
    public class Node<T> {
		T data;
		Node<T> next;
		
		public Node(T object) {
			this.data = object;
			next = null;
		}
	}

    //  Inserts a new object into the priority queue.  Returns true if
    //  the insertion is successful.  If the PQ is full, the insertion
    //  is aborted, and the method returns false.
    public boolean insert(E object) {
    	return insertLast(object);
    }
    
    public boolean insertFirst(E obj) {
    	Node<E> newNode = new Node<E>(obj);
    	if (isEmpty()) head = tail = newNode;
    	else {
    		newNode.next = head;
    		head = newNode;
    	}
    	currentSize++;
		return true;
    }
    
    public boolean insertLast(E obj) {
    	Node<E> newNode = new Node<E>(obj);
    	if (isEmpty()) head = tail = newNode;
    	else {
    		newNode.next = tail;
    		tail = newNode;
    	}
    	currentSize++;
    	return true;
    }
    
    //  Removes the object of highest priority that has been in the
    //  PQ the longest, and returns it.  Returns null if the PQ is empty.
    public E remove() {
    	return removeMin();
    }
    
    //helper method for remove()
    public E removeFirst() {
		if (head == null) return null;
		if (currentSize == 1){
			Node<E> temp = head;
			clear();
			return temp.data;
		}
		Node<E> current = head;
		head = head.next;
		currentSize--;
		return current.data;
    }

    //helper method for remove()
    public E removeMin() {
    	if (head == null) return null;
    	else if (currentSize == 1) return removeFirst();
    	
    	E temp = head.data;
    	Node<E> current = head, minPrev = null, previous = null, minCurr = null;
    	
    	while(current != null) {
    		if((current.data).compareTo(temp) < 0) {
    			temp = current.data;
    			minPrev = previous;
    			minCurr = current;
    		}
    		previous = current;
    		current = current.next;
    	}
    	
    	if(minPrev == null)	return removeFirst();
    	else if(minCurr==tail) {
    		minPrev.next = null;
    		tail = minPrev;
    	}
    	else{
    		minPrev.next = minCurr.next;
    		tail = minPrev.next;
    	}
    	currentSize--;
    	return temp;
	}

    
    //helper method for peek()
    public E findMin() {
    	if (head == null) return null;
    	
    	E temp = head.data;
    	Node<E> current = head;
    	
    	while(current != null) {
    		if((current.data).compareTo(temp) < 0) 
    			temp = current.data;
    		current = current.next;
    	}
    	return temp;
    }
   
    //  Returns the object of highest priority that has been in the
    //  PQ the longest, but does NOT remove it. 
    //  Returns null if the PQ is empty.
    public E peek() {
    	return findMin();
    }
    
    //  Returns true if the priority queue contains the specified element
    //  false otherwise.
    public boolean contains(E obj) {
    	if(head != null) return false;
    	
    	Node<E> current = head;
    	while (current!= null){
    		if ((current.data).compareTo(obj) == 0) return true;
    		current = current.next;
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
    }
   
    //  Returns true if the PQ is empty, otherwise false
    public boolean isEmpty() {
    	return currentSize == 0;
    }
   
    //  Returns true if the PQ is full, otherwise false.  List based
    //  implementations should always return false.
    public boolean isFull() {
    	return false;
    }
    
    class IteratorHelper implements Iterator<E> {
		Node<E> index;
		
		public IteratorHelper(){
			index = head;
		}
		
		public E next() {
			if (!hasNext())
				throw new NoSuchElementException();
			E tmp = index.data;
			index = index.next;
			return tmp;
		}
		
		public void remove() {
			throw new UnsupportedOperationException();
		}

		public boolean hasNext() {
			return (index != null);
		}
	}
    //  Returns an iterator of the objects in the PQ, in no particular
    //  order.  The iterator must be fail-fast.
    public Iterator<E> iterator() {
    	return new IteratorHelper();
    }
} 