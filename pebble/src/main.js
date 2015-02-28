/**Pebble.addEventListner("ready", function(e){
    var watchId = Pebble.getWatchToken();
});**/
/**
Pebble.addEventListener("appmessage", function(e){
    var watchId = 'qwrty';//Pebble.getWatchToken();
    
    var ajax = require('ajax');
    var packet = {
        "pebbleid":watchId
    };
    
    ajax(
        {
            url:'http://pqaeo749p6.database.windows.net/get_all_exercise_ids.php',
            type:'json',
            data: packet
        },
        function(data, status, request){
            console.log("data");
        },
         function(error, status, request){
            console.log('ajax failed');
        }        
    );    
});**/