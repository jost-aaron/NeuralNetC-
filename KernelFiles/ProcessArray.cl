void kernel ProcessArray(global int* data, global int* outData){

	outData[get_global_id(0)] = data[get_global_id(0)]*2;


}