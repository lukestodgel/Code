/**
 * cssc0956
 * 
 * Luke Stodgel
 * 5/1/2017
 */

package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class HashTable<K extends Comparable<K>, V> implements DictionaryADT<K, V> {

	int currentSize;
	int maxSize;
	long modCounter;
	int tableSize;
	UnorderedList<HashNode<K, V>>[] list;

	public HashTable(int size) {
		currentSize = 0;
		modCounter = 0;
		maxSize = size;
		tableSize = (int) ((int) maxSize * 1.3f);
		list = (UnorderedList<HashNode<K, V>>[]) new UnorderedList[tableSize];
		for (int i = 0; i < tableSize; i++)
			list[i] = new UnorderedList<HashNode<K, V>>();
	}

	private class HashNode<K, V> implements Comparable<HashNode<K, V>> {
		K key;
		V value;

		public HashNode(K key, V value) {
			this.key = key;
			this.value = value;
		}

		public int compareTo(HashNode<K, V> node) {
			return ((Comparable<K>) this.key).compareTo(node.key);
		}
	}

	public int getIndex(K key) {
		return key.hashCode() & 0x7FFFFFF % tableSize;
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

		int index = getIndex(key);
		for (HashNode<K, V> n : list[index])
			if (n.key.compareTo(key) == 0)
				return false;
		list[index].insertLast(new HashNode<K, V>(key, value));

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

		int index = getIndex(key);
		for (HashNode<K, V> n : list[index]) {
			if (n.key.compareTo(key) == 0)
				if (list[index].remove(n)) {
					currentSize--;
					modCounter++;
					return true;
				}
		}
		return false;
	}

	// Returns the value associated with the parameter key. Returns
	// null if the key is not found or the dictionary is empty.
	public V getValue(K key) {
		if (isEmpty())
			return null;

		int index = getIndex(key); // finds linked list to work with.
		for (HashNode<K, V> n : list[index])
			if (n.key.compareTo(key) == 0)
				return n.value;

		return null;
	}

	// Returns the key associated with the parameter value. Returns
	// null if the value is not found in the dictionary. If more
	// than one key exists that matches the given value, returns the
	// first one found.
	public K getKey(V value) {
		if (isEmpty()) return null;

		for (UnorderedList<HashNode<K, V>> ll : list) {
			for (HashNode<K, V> n : ll) {
				if (n.value.equals(value))
					return n.key;
			}
		}
		return null;
	}

	// Returns the number of key/value pairs currently stored
	// in the dictionary
	public int size() {
		return currentSize;
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
		for (int i = 0; i < tableSize; i++)
			list[i].clear();
		currentSize = 0;
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

		protected HashNode<K, V>[] nodes;
		protected int idx;
		protected long modCheck;

		public IteratorHelper() {
			nodes = new HashNode[currentSize];
			idx = 0;
			int j = 0;
			modCheck = modCounter;
			for (int i = 0; i < tableSize; i++)
				for (HashNode n : list[i])
					nodes[j++] = n;
			shellSort(nodes);
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

		public void shellSort(HashNode<K, V>[] array) {

			HashNode<K, V> temp;
			int out, in, h = 1;
			int size = array.length;

			while (h <= size / 3)
				h = h * 3 + 1;
			while (h > 0) {
				for (out = h; out < size; out++) {
					temp = array[out];
					in = out;
					while (in > h - 1 && array[in - h].compareTo(temp) <= 0) {
						array[in] = array[in - h];
						in -= h;
					}
					array[in] = temp;
				}
				h = (h - 1) / 3;
			}
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