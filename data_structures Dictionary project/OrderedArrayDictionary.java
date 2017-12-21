/**
 * cssc0956
 * 
 * Luke Stodgel
 */

package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class OrderedArrayDictionary<K extends Comparable<K>, V> implements DictionaryADT<K, V> {

	DictionaryNode<K, V>[] array;
	private int currentSize;
	private int maxSize;
	private long modCounter;

	public OrderedArrayDictionary() {
		currentSize = 0;
		maxSize = 100000;
		array = (DictionaryNode<K, V>[]) new DictionaryNode[(int) (maxSize * 1.3f)];
	}
	
	public OrderedArrayDictionary(int size) {
		currentSize = 0;
		maxSize = size;
		array = (DictionaryNode<K, V>[]) new DictionaryNode[(int) (maxSize * 1.3f)];
	}

	private class DictionaryNode<K, V> implements Comparable<DictionaryNode<K, V>> {
		K key;
		V value;

		public DictionaryNode(K key, V value) {
			this.key = key;
			this.value = value;
		}

		public int compareTo(DictionaryNode<K, V> node) {
			return ((Comparable<K>) this.key).compareTo(node.key);
		}
	}

	// Returns true if the dictionary has an object identified by
	// key in it, otherwise false.
	public boolean contains(K key) {
		return getValue(key) != null;
	}

	// Adds the given key/value pair to the dictionary. Returns
	// false if the dictionary is full, or if the key is a duplicate.
	// Returns true if addition succeeded.
	public boolean add(K key, V value) {
		if (isFull())
			return false;

		int index = binSearch(key, 0, currentSize - 1);

		if (array[index] != null && array[index].key.compareTo(key) == 0)
			return false;

		for (int i = currentSize - 1; i >= index; i--)
			array[i+1] = array[i];

		array[index] = new DictionaryNode<K, V>(key, value);

		currentSize++;
		modCounter++;
		return true;
	}

	// Deletes the key/value pair identified by the key parameter.
	// Returns true if the key/value pair was found and removed,
	// otherwise false.
	public boolean delete(K key) {
		if (isEmpty())
			return false;

		int index = binSearch(key, 0, currentSize-1);

		if (array[index].key.compareTo(key) == 0)
			for (int i = index; i < currentSize-1; i++)
				array[i] = array[i+1];

		modCounter++;
		currentSize--;
		return true;
	}

	// Returns the value associated with the parameter key. Returns
	// null if the key is not found or the dictionary is empty.
	public V getValue(K key) {
		if (isEmpty())
			return null;

		int index = binSearch(key, 0, currentSize - 1);
														
			if (array[index].key.compareTo(key) == 0)
				return array[index].value;

		return null;

	}

	// Returns the key associated with the parameter value. Returns
	// null if the value is not found in the dictionary. If more
	// than one key exists that matches the given value, returns the
	// first one found.
	public K getKey(V value) {
		if (isEmpty())
			return null;

		for (DictionaryNode<K, V> n : array) {
			if (n.value.equals(value))
				return n.key;
		}
		return null;
	}

	// Returns the number of key/value pairs currently stored
	// in the dictionary
	public int size() {
		return array.length;
	}

	// Returns true if the dictionary is at max capacity
	public boolean isFull() {
		return currentSize >= maxSize;
	}

	// Returns true if the dictionary is empty
	public boolean isEmpty() {
		return currentSize == 0;
	}

	// Returns the Dictionary object to an empty state.
	public void clear() {
		currentSize = 0;
	}

	// binSearch
	public int binSearch(K obj, int lo, int hi) {
		if (hi < lo)
			return lo;
		int mid = (lo + hi) >> 1;
		int c = obj.compareTo(array[mid].key);
		if (c <= 0)
			return binSearch(obj, lo, mid - 1); // go left
		return binSearch(obj, mid + 1, hi); // go right
	}

	// Returns an Iterator of the keys in the dictionary, in ascending
		// sorted order. The iterator must be fail-fast.
		public Iterator<K> keys() {
			return new KeyIteratorHelper();
		}

		// Returns an Iterator of the values in the dictionary. The
		// order of the values must match the order of the keys.
		// The iterator must be fail-fast.
		public Iterator<V> values() {
			return new ValueIteratorHelper();
		}

		abstract class IteratorHelper<E> implements Iterator<E> {

			protected DictionaryNode<K, V>[] nodes;
			protected int idx;
			protected long modCheck;

			public IteratorHelper() {
				nodes = new DictionaryNode[currentSize];
				idx = 0;
				modCheck = modCounter;
					for(int i =0; i < currentSize;i++){
						nodes[i] = array[i];
					}
			}

			public boolean hasNext() {
				if (modCheck != modCounter)
					throw new ConcurrentModificationException();
				return idx < currentSize;
			}

			public abstract E next();

			public void remove() {
				throw new UnsupportedOperationException();
			}
		}

		class KeyIteratorHelper extends IteratorHelper<K> {
			public KeyIteratorHelper() {
				super();
			}

			public K next() {
				return (K) nodes[idx++].key;
			}
		}

		class ValueIteratorHelper extends IteratorHelper<V> {
			public ValueIteratorHelper() {
				super();
			}

			public V next() {
				return (V) nodes[idx++].value;
			}
		}
	}