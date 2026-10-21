package str

// NodeStatus represents the state of a hash node.
type NodeStatus int

const (
	EMPTY   NodeStatus = iota
	USED    NodeStatus = iota
	DELETED NodeStatus = iota
)

// HashNode is a single slot in the open-addressing hash map.
type HashNode struct {
	Status NodeStatus
	Val    string
}

// Map is an open-addressing hash map with double hashing.
type Map struct {
	Sz    int
	Cap   int
	Nodes []HashNode
}

// NewMap creates a new Map with the given capacity (minimum 16).
func NewMap(capacity int) Map {
	if capacity < 16 {
		capacity = 16
	}
	nodes := make([]HashNode, capacity)
	for i := range nodes {
		nodes[i].Status = EMPTY
	}
	return Map{Sz: 0, Cap: capacity, Nodes: nodes}
}

// hashDjb2 computes the djb2 hash of a key.
func hashDjb2(key string) int {
	var hash uint64 = 5381
	for i := 0; i < len(key); i++ {
		hash = ((hash << 5) + hash) + uint64(key[i])
	}
	return int(hash % (1<<63 - 1))
}

// hashFnv1a computes the FNV-1a hash of a key.
func hashFnv1a(key string) int {
	var hash uint64 = 14695981039346656037
	for i := 0; i < len(key); i++ {
		hash ^= uint64(key[i])
		hash *= 1099511628211
	}
	return int(hash % (1<<63 - 1))
}

// hashStep computes the probe step using FNV-1a (always odd).
func hashStep(key string, cap int) int {
	step := hashFnv1a(key) % cap
	if step < 0 {
		step = -step
	}
	if step == 0 {
		step = 1
	}
	if step%2 == 0 {
		step++
	}
	return step
}

// Find returns the index of val in the map, or -1 if not found.
func (m *Map) Find(val string) int {
	idx := hashDjb2(val) % m.Cap
	if idx < 0 {
		idx = -idx
	}
	if m.Nodes[idx].Status == USED && m.Nodes[idx].Val == val {
		return idx
	} else if m.Nodes[idx].Status == EMPTY {
		return -1
	}
	step := hashStep(val, m.Cap)
	i := (idx + step) % m.Cap
	for i != idx {
		if m.Nodes[i].Status == USED && m.Nodes[i].Val == val {
			return i
		}
		if m.Nodes[i].Status == EMPTY {
			return -1
		}
		i = (i + step) % m.Cap
	}
	return -1
}

// Insert inserts val into the map if not already present.
// Panics if the table is full. Restructures if load > 0.9.
func (m *Map) Insert(val string) {
	if m.Find(val) != -1 {
		return
	}
	if m.Sz == m.Cap {
		panic("hash map is full")
	}
	idx := hashDjb2(val) % m.Cap
	if idx < 0 {
		idx = -idx
	}
	if m.Nodes[idx].Status == EMPTY || m.Nodes[idx].Status == DELETED {
		m.Nodes[idx].Val = val
		m.Nodes[idx].Status = USED
	} else {
		newIdx := -1
		step := hashStep(val, m.Cap)
		i := (idx + step) % m.Cap
		for i != idx {
			if m.Nodes[i].Status == EMPTY || m.Nodes[i].Status == DELETED {
				newIdx = i
				break
			}
			i = (i + step) % m.Cap
		}
		if newIdx == -1 {
			panic("hash map is full")
		}
		m.Nodes[newIdx].Val = val
		m.Nodes[newIdx].Status = USED
	}
	m.Sz++

	if float64(m.Sz)/float64(m.Cap) > 0.9 {
		m.restruct()
	}
}

// Del marks the slot as DELETED. Returns false if not found.
func (m *Map) Del(val string) bool {
	idx := m.Find(val)
	if idx == -1 {
		return false
	}
	m.Nodes[idx].Status = DELETED
	m.Nodes[idx].Val = ""
	m.Sz--
	return true
}

// restruct doubles the capacity and reinserts all USED nodes.
func (m *Map) restruct() {
	newMap := NewMap(m.Cap * 2)
	for i := 0; i < m.Cap; i++ {
		if m.Nodes[i].Status == USED {
			newMap.Insert(m.Nodes[i].Val)
		}
	}
	m.Nodes = newMap.Nodes
	m.Sz = newMap.Sz
	m.Cap = newMap.Cap
}

