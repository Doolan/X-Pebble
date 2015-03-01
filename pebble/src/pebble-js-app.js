//Executes on open
Pebble.addEventListener('ready', function(e) {
    console.log('JavaScript app ready and running!');
    getWorkout();
  }
);

//listens for App Messages
Pebble.addEventListener('appmessage',function(e){
    //FOR STATS MOST LIKELY NOT IN THIS BUILD
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
    //TOPEBBLE: Step 1 get request
    var url = "http://x-pebble.azurewebsites.net/scripts/get_all_exercise_ids.php?pebbleid=qwerty";    
    //send request to Josh for the data
    xhrRequest(url, 'GET', function(responseText){
        var exerciseString = JSON.parse(responseText);   
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


