void kernel opp(global double* data, global double* outData){

	outData[get_global_id(0)] = data[get_global_id(0)];


}