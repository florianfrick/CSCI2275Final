# CSCI2275Final

My project is meant to represent the ordering and production of a product at a store or factory. The orderer and their "tab" is kept track of in a dictionary as they order more products. A priority queue, implemented as a heap, determines what orders are fulfilled first. Part of the program allows the ordering of more products while another part simulates fulfilling these requests in a proper order.

To compile, enter g++ -std=c++1 Dictionary.cpp PriorityQueueHeap.cpp Product.cpp Warehouse.cpp

To run, enter ./a.out productstockcost.txt orders.txt
where the first file is a comma separated list with product names, stock of product in warehouse, cost of product
and the second file is a comma separated list with customer name, name of product, order amount