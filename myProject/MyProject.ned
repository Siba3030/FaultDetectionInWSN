package node.application.myProject;
simple MyProject like node.application.iApplication
{
    parameters:
        string applicationID = default("myProject");
        bool collectTraceInfo = default(true);
        int priority = default(1);
        int packetHeaderOverhead = default(8);	// in bytes
        int constantDataPayload = default(2);	// in bytes
        double tempThreshold = default(3.0);

    gates:
        output toCommunicationModule;
        output toSensorDeviceManager;
        input fromCommunicationModule;
        input fromSensorDeviceManager;
        input fromResourceManager;
}

