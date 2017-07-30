class Arc {
	
	public int v1, v2;
	
	public Arc(int v1, int v2) {
		this.v1 = v1;
		this.v2 = v2;
	}
	
	public int hashCode() {
		int h = 17;
		h = h*31 + v1;
		h = h*31 + v2;
		return  h;
	}
	
	public boolean equals(Object that) {
		Arc other = (Arc) that;
		if(other.v1 == v1 && other.v2 == v2) {
			return true;
		}
		return false;
	}
}
