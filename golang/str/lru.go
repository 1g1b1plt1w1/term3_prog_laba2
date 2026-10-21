package str

import "math"

const lruMaxCap = 256 * 256

// LruNode is a single entry in the LRU cache.
type LruNode struct {
	LastUsed int
	Key      string
	Value    string
}

// Lru is a simple LRU cache backed by a flat array.
type Lru struct {
	Cap   int
	Sz    int
	Nodes []LruNode
}

// NewLru creates a new LRU cache with the given capacity (min 1, max 256*256).
func NewLru(capacity int) Lru {
	if capacity < 1 {
		capacity = 1
	}
	if capacity > lruMaxCap {
		capacity = lruMaxCap
	}
	return Lru{
		Cap:   capacity,
		Sz:    0,
		Nodes: make([]LruNode, capacity),
	}
}

// Get returns the value for key, updating LastUsed. Returns "-1" if not found.
func (l *Lru) Get(key string, step int) string {
	for i := 0; i < l.Sz; i++ {
		if l.Nodes[i].Key == key {
			l.Nodes[i].LastUsed = step
			return l.Nodes[i].Value
		}
	}
	return "-1"
}

// Set sets or updates a key-value pair, evicting the LRU entry if full.
func (l *Lru) Set(key string, value string, step int) {
	// Update existing key
	for i := 0; i < l.Sz; i++ {
		if l.Nodes[i].Key == key {
			l.Nodes[i].Key = key
			l.Nodes[i].Value = value
			l.Nodes[i].LastUsed = step + 1
			return
		}
	}
	// Evict LRU if full
	if l.Sz >= l.Cap {
		minLastUsed := math.MaxInt64
		delIdx := 0
		for i := 0; i < l.Cap; i++ {
			if l.Nodes[i].LastUsed < minLastUsed {
				minLastUsed = l.Nodes[i].LastUsed
				delIdx = i
			}
		}
		l.Nodes[delIdx].Key = key
		l.Nodes[delIdx].Value = value
		l.Nodes[delIdx].LastUsed = step + 1
	} else {
		l.Nodes[l.Sz].Key = key
		l.Nodes[l.Sz].Value = value
		l.Nodes[l.Sz].LastUsed = step + 1
		l.Sz++
	}
}

