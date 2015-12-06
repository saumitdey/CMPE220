function placeAnOrder(orderNumber){
    console.log("Customer order", orderNumber);

        cookanddeliver(function(){
            console.log("Delivered food order:", orderNumber);
        });
}
//Simulate a 5 second operation
function cookanddeliver(callback){
    setTimeout(callback,5000); // in other words it requests data from the database
}

placeAnOrder(1);
placeAnOrder(2);
placeAnOrder(3);
placeAnOrder(4);


