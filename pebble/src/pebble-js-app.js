//Executes on open
Pebble.addEventListener('ready', function(e) {
    console.log('JavaScript app ready and running!');
    getWorkout();
  }
);



//listens for App Messages
Pebble.addEventListener('appmessage',function(e){
    console.log("AppMessage received!");
});

//XMLHttpRequests
var xhrRequest = function(url, type, callback){
    var xhr = new XMLHttpRequest();
    xhr.onload = function() {
        callback(this.responseText);
    };
    xhr.open(type, url);
    xhr.send();
};


//TOPEBBLE: Step 1 get request
function getWorkout(){
    console.log('hit get workout');
    
    //TOPEBBLE: Step 1 get request
    var url = "http://x-pebble.azurewebsites.net/scripts/get_all_exercise_ids.php?pebbleid=qwerty";    
    //send request to Josh for the data
    xhrRequest(url, 'GET', function(responseText){
        var exerciseString = JSON.parse(responseText);
        console.log(responseText, exerciseString);
     
   // var array = new Uint8Array(100);
    // array1 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16];
    
        //TOPEBBLE: Step 2, build Dictionary (required)
        var mydictionary = {
           "KEY_WORKOUTPLAN": exerciseString
        };
        //TOPEBBLE: Send to Pebble 
        Pebble.sendAppMessage(mydictionary,
              function(e){
                 console.log("send stuff to pebble -- success");
              },
              function(e){
                  console.log("error-ed on send");
              });
       });
}


