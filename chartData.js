function fetchdata(){
    //setInterval($.ajax, 1000);
    $.ajax({
        //async:false,
        url: "https://gggguj.000webhostapp.com/bpmGET.php",
        method: "GET",
        success: function(data) {
            //console.log(data);
            var player = [];
            var score = [];
            var ecg =[];

            for(var i in data) {
                player.push(data[i].id);
                ecg.push(data[i].value3); //mV ECG value
                score.push(data[i].value4); //bpm value
            }

            var bpm_Min = Math.min(...score);
            var bpm_Max = Math.max(...score);
            var bpm_Current = score[0];
            
            // console.log(bpm_Current);
            // console.log(player);
            // console.log(score);
            // console.log(bpm_Current);
            //$("#currentBPM2").hide();
            $("#minBPM").append(" " + bpm_Min);
            $("#maxBPM").append(" " + bpm_Max);
            $("#currentBPM").append(" " + bpm_Current);
            $("#currentBPM2").append(" " + bpm_Current); //copy from above as ID cant be shared

            
            var playerRev = player.reverse();
            var ecgRev = ecg.reverse();
            
            var chartdata = {
                labels: playerRev,
                datasets: [
                    {
                        //fill: true,
                        //backgroundColor: '#c31432',
                        //rgb(54, 162, 235)
                        // backgroundColor: ['rgba(54, 162, 235, 0.3)', 'rgba(0,187,122,0.3)', 'rgba(254,176,25,0.3)'],
                        // borderColor: ['rgb(54, 162, 235)', 'rgb(0,187,122)', 'rgb(254,176,25)'],
                        backgroundColor: "rgba(255,255,255,0)",
                        borderColor: "rgba(82,185,159,1)",
                        pointBackgroundColor: "rgba(82,185,159,1)",
                        pointBorderColor: "#fff",
                        pointHoverBackgroundColor: "#fff",
                        pointHoverBorderColor: "rgba(82,185,159,1)",

                        //borderWidth: 2,
                        pointRadius: 0,
                        data: ecgRev
                    }
                ]
            };
			
            var ctx = $("#myChart2");

            var barGraph = new Chart(ctx, {
                type: 'line',
                data: chartdata,

                options: {
                    title: {
                        display: true,
                        text: 'ECG (in mV)' 
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
                                //max: 175,
                                min: 1,
                                stepSize: 50,
                                display: false
                            }

							

                        }],

                        yAxes: [{
					
                            ticks: {
                                max: 800,
                                min: 300,
                                stepSize: 100
                            },

                            gridLines: {
                                // display: false
                            }
                        }]
                    }
                },


            });

            
            
        }
    });

    
        
};

$(document).ready(function(){
    // setInterval(fetchdata,1000);
    
    fetchdata();
    });



