package str

// Set wraps Map to provide a set data structure.
type Set struct {
	M Map
}

// NewSet creates a new Set with the given capacity.
func NewSet(capacity int) Set {
	return Set{M: NewMap(capacity)}
}

// Add adds a value to the set.
func (s *Set) Add(value string) {
	s.M.Insert(value)
}

// Del removes a value from the set. Returns false if not found.
func (s *Set) Del(value string) bool {
	return s.M.Del(value)
}

// Has returns true if the value is in the set.
func (s *Set) Has(value string) bool {
	return s.M.Find(value) != -1
}

// Keys returns all values currently in the set (USED slots).
func (s *Set) Keys() []string {
	var result []string
	for i := 0; i < s.M.Cap; i++ {
		if s.M.Nodes[i].Status == USED {
			result = append(result, s.M.Nodes[i].Val)
		}
	}
	return result
}

