
//==================================================//
//==========Table Parsing====ECG HEART RATE=====//
//==================================================//

$.post('https://gggguj.000webhostapp.com/bpmGET.php', function(data) {
    $.each(data, function(i, item) {
        //calStatus = item.status;
        //console.log(item);
        // var item1 = [item.id].reverse();
        $("#tableOne").append("<tr>" +
                                "<td>" + item.id + "</td>" + 
                                "<td>" + item.value3 + "</td>" +
                                "<td>" + item.value4 + "</td>" +
                                "<td>" + item.reading_time + "</td>" +
                            "</tr>"
                                );
    });
});

//==================================================//
//==========Table Parsing====Body Temp=====//
//==================================================//

$.post('https://gggguj.000webhostapp.com/tempGET.php', function(data) {
    $.each(data, function(i, item) {
        //calStatus = item.status;
        //console.log(item);
        
        $("#tableTwo").append("<tr>" +
                                "<td>" + item.id + "</td>" + 
                                "<td>" + item.value1 + "</td>" +
                                "<td>" + item.reading_time + "</td>" +
                            "</tr>"
                                );
    });
});

//==================================================//
//==========Table Parsing====HAR =====//
//==================================================//

$.post('https://gggguj.000webhostapp.com/actionGET.php', function(data) {
    $.each(data, function(i, item) {
        //calStatus = item.status;
        //console.log(item);
        
        $("#tableThree").append("<tr>" +
                                "<td>" + item.id + "</td>" + 
                                "<td>" + item.value13 + "</td>" +
                                "<td>" + item.value14 + "</td>" +
                                "<td>" + item.value15 + "</td>" +
                                "<td>" + item.value16 + "</td>" +
                                "<td>" + item.reading_time + "</td>" +
                            "</tr>"
                                );
    });
});


//====================================================//
//==========Table Parsing==== Indoor Positioning =====//
//====================================================//

$.post('https://gggguj.000webhostapp.com/mapGET.php', function(data) {
    $.each(data, function(i, item) {
        //calStatus = item.status;
        // console.log(item.value11);
        
        $("#tableFour").append("<tr>" +
                                "<td>" + item.id + "</td>" + 
                                "<td>" + item.value11 + "</td>" +
                                "<td>" + item.value12 + "</td>" +
                                "<td>" + item.reading_time + "</td>" +
                            "</tr>"
                                );
    });
});


//====================================================//
//==========Table Parsing==== POWER MANAGEMENT =====//
//====================================================//

$.post('https://gggguj.000webhostapp.com/powerGET.php', function(data) {
    $.each(data, function(i, item) {
        //calStatus = item.status;
        // console.log(item.value11);
        
        $("#tableFive").append("<tr>" +
                                "<td>" + item.id + "</td>" + 
                                "<td>" + item.value8 + "V"+ "</td>" +
                                "<td>" + item.value9 + "A"+"</td>" +
                                "<td>" + item.value7 + "%"+"</td>" +
                                "<td>" + item.reading_time + "</td>" +
                            "</tr>"
                                );
    });
});




