chord_base: chord_base.cpp
	g++ chord_base.cpp -o chord_base
	./chord_base

chord_time_nodeJoin: chord_time_nodeJoin.cpp
	g++ chord_time_nodeJoin.cpp -o chord_time_nodeJoin
	./chord_time_nodeJoin

chord_time_keyInsert: chord_time_keyInsert.cpp
	g++ chord_time_keyInsert.cpp -o chord_time_keyInsert
	./chord_time_keyInsert

chord_hop_keyInsert: chord_hop_keyInsert.cpp
	g++ chord_hop_keyInsert.cpp -o chord_hop_keyInsert
	./chord_hop_keyInsert

chord_hop_pathvsnodes: chord_hop_pathvsnodes.cpp
	g++ chord_hop_pathvsnodes.cpp -o chord_hop_pathvsnodes
	./chord_hop_pathvsnodes

clean:
	rm -rf chord_base chord_time_nodeJoin chord_time_keyInsert chord_hop_keyInsert chord_hop_pathvsnodes
