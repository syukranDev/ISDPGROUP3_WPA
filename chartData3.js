$(document).ready(function(){
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/actionGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var score = [];
            var value_X = [];
            var value_Y = [];
            var value_Z = [];
            var action =[];

            for(var i in data) {
                player.push(data[i].id);
                score.push(data[i].value13);
                value_X.push(data[i].value13);
                value_Y.push(data[i].value14);
                value_Z.push(data[i].value15);
                action.push(data[i].value16);

            }

         
            //Pull current value of XYZ 
            $("#valueX").append(" " + value_X[0]);
            $("#valueY").append(" " + value_Y[0]);
            $("#valueZ").append(" " + value_Z[0]);

            //Pull Action Data
            $("#currentAction").append(" " + action[0]);
            $("#currentAction1").append(" " + action[0]);

            var player_rev = player.reverse();
            var score_rev = score.reverse();

            var chartdata = {
                labels: player_rev,
                datasets: [
                    {
                        //fill: true,
                        //backgroundColor: '#c31432',
                        //rgb(54, 162, 235)
                        // backgroundColor: ['rgba(54, 162, 235, 0.3)', 'rgba(0,187,122,0.3)', 'rgba(254,176,25,0.3)'],
                        // borderColor: ['rgb(54, 162, 235)', 'rgb(0,187,122)', 'rgb(254,176,25)'],
                        backgroundColor: "rgba(255,255,255,0)",
                        borderColor: "rgba(236,83,62,1)",
                        pointBackgroundColor: "rgba(236,83,62,1)",
                        pointBorderColor: "#fff",
                        pointHoverBackgroundColor: "#fff",
                        pointHoverBorderColor: "rgba(236,83,62,1)",

                        borderWidth: 2, //kecik sikit 2
                        pointRadius: 0,
                        data: score_rev
                    }
                ]
            };
			
            var ctx = $("#myChart3");

            var barGraph = new Chart(ctx, {
                type: 'line',
                data: chartdata,

                options: {
                    title: {
                        display: true,
                        text: 'X-value (in Degree)' 
                    },

                    legend: {
                        display: false,
						
                    },
                    scales: {
                        xAxes: [{
                            gridLines: {
                                 display: false
                            },

                            ticks: {
                                max: 200,
                                min: 1,
                                stepSize: 100,
                                display: false
                            }

							

                        }],

                        yAxes: [{
					
                            ticks: {
                                max: 180,
                                min: -180,
                                stepSize: 90
                            },

                            gridLines: {
                                // display: false
                            }
                        }]
                    }
                },


            });

            // setInterval(function(){
            //     $.ajax();
            //     }, 10000);
			
            
          
        }
    });
});