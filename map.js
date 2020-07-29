$(document).ready(function(){
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/mapGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var score = [];
          

            for(var i in data) {
                player.push(data[i].value11);
                score.push(data[i].value12);
            }


            var locX = player[0];
            var locY = score[0];
            var locX_1 = parseFloat(locX).toFixed(2);
            var locY_1 = parseFloat(locY).toFixed(2);


            // var locY = score[0].toFixed(2);
            console.log(locX_1);
            $("#currentLocation_X").append(locX_1);
            $("#currentLocation_Y").append(locY_1);

            var mymap = L.map('mapid').setView([4.381935, 100.970111],15);

            //check point marker A b C D 
            L.circle([4.383561, 100.966667], {
                color: '#3388ff',
                fillColor: '#3388ff',
                fillOpacity: 0.2,
                radius: 100
            }).addTo(mymap).bindPopup('Checkpoint A').openPopup();
            L.circle([4.382192, 100.964597], {
                color: '#3388ff',
                fillColor: '#3388ff',
                fillOpacity: 0.5,
                radius: 100
            }).addTo(mymap).bindPopup('Checkpoint B').openPopup();
            L.circle([4.380844, 100.967322], {
                color: '#3388ff',
                fillColor: '#3388ff',
                fillOpacity: 0.5,
                radius: 100
            }).addTo(mymap).bindPopup('Checkpoint C').openPopup();
            L.circle([4.381924, 100.969500], {
                color: '#3388ff',
                fillColor: '#3388ff',
                fillOpacity: 0.5,
                radius: 100
            }).addTo(mymap).bindPopup('Checkpoint D').openPopup();

            L.marker([player[0],score[0]]).addTo(mymap).bindPopup('You\'re here!').openPopup();

            
      
            // var circle = L.circle([player[3], score[3]], {
            //     color: '#0000FF',
            //     fillColor: '#0000FF',
            //     fillOpacity: 0.5,
            //     radius: 10
            // }).addTo(mymap);

            // var circle = L.circle([player[2], score[2]], {
            //     color: '#0000FF',
            //     fillColor: '#0000FF',
            //     fillOpacity: 0.5,
            //     radius: 10
            // }).addTo(mymap);

            // var circle = L.circle([player[1], score[1]], {
            //     color: '#0000FF',
            //     fillColor: '#0000FF',
            //     fillOpacity: 0.5,
            //     radius: 10
            // }).addTo(mymap);

            // var circle = L.circle([player[4], score[4]], {
            //     color: '#0000FF',
            //     fillColor: '#0000FF',
            //     fillOpacity: 0.5,
            //     radius: 10
            // }).addTo(mymap);

        

            var player_rev = player.reverse();
            var score_rev = score.reverse();

            var latlngs = player_rev.map((l, i) => [l, score_rev[i]]);


            // console.log(latlngs_rev);

            // var latlngs = [
            // [4.381918, 100.968257],
            // [4.382362, 100.967436],
            // [4.383394, 100.966766],
            // [4.384060, 100.966685],
            // [4.384878, 100.966578],
            // [4.385664, 100.966487],
            // [4.386130, 100.966423],
            // [4.386584, 100.966423],
            // [4.387146, 100.966310],
            // [4.387531, 100.966315],
            // [4.387483, 100.965065],
            // [4.387344, 100.964293],
            // [4.386916, 100.963644],
            // [4.386098, 100.963966]
            // ]; 
        
            var path = L.polyline.antPath(latlngs, {
                "delay": 400,
                "dashArray": [
                    14,
                    20
                ],
                "weight": 5,
                "color": "#0000FF",
                "pulseColor": "#FFFFFF",
                "paused": false,
                "reverse": false,
                "hardwareAccelerated": true
                }).addTo(mymap);
        
            mymap.addLayer(path);
            mymap.fitBounds(path.getBounds());
            L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                maxZoom: 19
                //attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors' -->
            }).addTo(mymap);
        }
    });
});


    