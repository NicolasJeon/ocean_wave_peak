import QtQuick

SeaSurfaceForm {
    WaveDataProxy {
        id: waveDataProxyId
    }

    Component.onCompleted: {
        surfaceSeriesId.dataProxy = waveDataProxyId;
        console.log("Data Proxy Set:", surfaceSeriesId.dataProxy !== null);
    }

    Connections {
        target: waveDataProxyId
        function onHighestPeakChanged () {
            markerId.visible = true;
            labelId.visible = true;

            // Animate the marker's position
            markerPositionAnimation.from = markerId.position
            markerPositionAnimation.to = waveDataProxyId.highestPeakPos
            markerPositionAnimation.running = true

            // Animate the label's position
            labelPositionAnimation.from = labelId.position
            labelPositionAnimation.to = waveDataProxyId.highestPeakLabelPos
            labelPositionAnimation.running = true

            labelId.text = " Highest Peak: " + waveDataProxyId.highestPeakPos.y.toFixed(1) + " M ";
        }
    }

    Vector3dAnimation {
        id: markerPositionAnimation
        target: markerId
        property: "position"
        duration: 150 // Adjust duration as needed (in milliseconds)
    }

    Vector3dAnimation {
        id: labelPositionAnimation
        target: labelId
        property: "position"
        duration: 150
    }
}
