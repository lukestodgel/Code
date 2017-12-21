/**
 * cssc0956
 * 
 * Luke Stodgel
 */

package data_structures;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class BinarySearchTree<K extends Comparable<K>, V> implements DictionaryADT<K, V> {

	int maxSize;
	int currentSize;
	long modCounter;
	TreeNode<K, V> root;

	public BinarySearchTree() {
		currentSize = 0;
		root = null;
	}

	private class TreeNode<K, V> implements Comparable<TreeNode<K, V>> {
		K key;
		V value;
		TreeNode<K, V> leftChild, rightChild;
		boolean isLeftChild;

		public TreeNode(K key, V value) {
			this.key = key;
			this.value = value;
			leftChild = rightChild = null;
		}

		public int compareTo(TreeNode<K, V> node) {
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
		if (root == null) {
			root = new TreeNode<K, V>(key, value);
			currentSize++;
			modCounter++;
		} else {
			TreeNode<K, V> toAdd = new TreeNode<K, V>(key, value);
			return insert(toAdd, root);
		}
		return false;
	}

	// Helper method for add().
	private boolean insert(TreeNode<K, V> toAdd, TreeNode<K, V> n) {
		if (toAdd.compareTo(n) < 0) {
			if (n.leftChild == null) {
				n.leftChild = toAdd;
				toAdd.isLeftChild = true;
				currentSize++;
				modCounter++;
				return true;
			}
			return insert(toAdd, n.leftChild);
		}
		if (toAdd.compareTo(n) > 0) {
			if (n.rightChild == null) {
				n.rightChild = toAdd;
				toAdd.isLeftChild = false;
				currentSize++;
				modCounter++;
				return true;
			}
			return insert(toAdd, n.rightChild);
		}
		return false;
	}

	// Deletes the key/value pair identified by the key parameter.
	// Returns true if the key/value pair was found and removed,
	// otherwise false.
	public boolean delete(K key) {
		if (delete(root, null, key)) {
			currentSize--;
			modCounter++;
			return true;
		}
		return false;
	}

	private boolean delete(TreeNode<K, V> n, TreeNode<K, V> parent, K k) {
		if (n == null)
			return false;
		if (n.key.compareTo(k) > 0) { // is it left?
			return delete(n.leftChild, n, k);
		} else if (n.key.compareTo(k) < 0) { // is it right?
			return delete(n.rightChild, n, k);
		} else { // here
			if (n.leftChild == null && n.rightChild == null) {
				if (parent == null)
					root = null;
				else if (n.isLeftChild)
					parent.leftChild = null;
				else
					parent.rightChild = null;
				n = null;
				return true;
			} else if (n.leftChild == null && n.rightChild != null || n.leftChild != null && n.rightChild == null) {
				if (n.leftChild != null) {

					if (parent == null)
						root = n.leftChild;
					if (n.isLeftChild)
						parent.leftChild = n.leftChild;
					else {
						parent.rightChild = n.leftChild;
						n.leftChild.isLeftChild = false;

					}
					n = n.leftChild;
				}
				if (n.rightChild != null) {

					if (parent == null)
						root = n.rightChild;
					if (n.isLeftChild)
						parent.leftChild = n.rightChild;
				} else {
					parent.rightChild = n.rightChild;
					n.rightChild.isLeftChild = false;
				}
				n = n.rightChild;
				return true;
			} else {
				TreeNode<K, V> node = findMinimumNode(n.rightChild);
				n.key = node.key;
				n.value = node.value;
				return delete(n.rightChild, parent, node.key);
			}
		}
	}

	// finds minimum node in a tree.
	private TreeNode<K, V> findMinimumNode(TreeNode<K, V> node) {
		if (node.leftChild == null)
			return node;
		return findMinimumNode(node.leftChild);
	}

	// Returns the value associated with the parameter key. Returns
	// null if the key is not found or the dictionary is empty.
	public V getValue(K key) {
		return find(key, root);
	}

	// Helper method for getValue().
	private V find(K k, TreeNode<K, V> n) {
		if (n == null)
			return null;
		if (k.compareTo((K) n.key) < 0)
			return find(k, n.leftChild);
		else if (k.compareTo((K) n.key) > 0)
			return find(k, n.rightChild);
		return (V) n.value;
	}

	// Returns the key associated with the parameter value. Returns
	// null if the value is not found in the dictionary. If more
	// than one key exists that matches the given value, returns the
	// first one found.
	public K getKey(V value) {
		if (isEmpty())
			return null;
		return getKey(root, value);
	}

	private K getKey(TreeNode<K, V> n, V value) {
		if (n == null)
			return null;
		if (getKey(n.leftChild, value) != null)
			return getKey(n.leftChild, value);
		if (n.value.equals(value))
			return n.key;
		return getKey(n.rightChild, value);
	}

	// Returns the number of key/value pairs currently stored
	// in the dictionary
	public int size() {
		return currentSize;
	}

	// Returns true if the dictionary is at max capacity
	public boolean isFull() {
		return false;
	}

	// Returns true if the dictionary is empty
	public boolean isEmpty() {
		return root == null;
	}

	// Returns the Dictionary object to an empty state.
	public void clear() {
		root = null;
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

		protected TreeNode<K, V>[] nodes;
		protected int idx;
		protected long modCheck;
		
		public IteratorHelper() { // THIS DOES NOT LOOK RIGHT
			nodes = new TreeNode[currentSize];
			idx=0;
			iterate(root);
			idx = 0;
			modCheck = modCounter;
		}

		public void iterate(TreeNode<K, V> n) {
			if (n == null)
				return;
			iterate(n.leftChild);
			nodes[idx++] = n;
			iterate(n.rightChild);
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
			if (!hasNext())
				throw new NoSuchElementException(); // YASDFASDFJAWEF
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