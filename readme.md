# Realtime Embedded Datalogger Visualization

*hldata: high low data*

*Realtime data logging application that flows from embedded device, to cloud/server/database, to output visualization. Uses modern technology to achieve data analytics quickly and for low cost.*

This project has three main elements:

* **Logger**: An embedded hardware device that operates wirelessly and on battery, which periodically sends data to a server running in the cloud. In the event that internet connectivity is not available, it stores data locally until a time at which it can ship data up to a specified server
* **Cloud/Server**: A server running containerized app code that listens to incoming POST requests from loggers and responds to incoming GET requests from visualization destinations; both receiving/sending log data from the local database respectively (using Docker, Docker Compose, MongoDB, Node.js, Express, and Digital Ocean). This portion of the architecture could also server as a source to push messages to bots/other platforms when certain conditions are met. It could also listen to configuration destinations and send back configuration data to the loggers as they reconnect to send new data from their endpoints, enabling bi-directional communication.
* **Visualizations**: A place to view data from each logger. This can take any form and can be developed in any language/platform so long as that platform supports REST calls. You could build a website, a task tray application, a desktop application, a mobile application, an embedded hardware monitor, etc. And visualizations can take any of a number of forms.

**Cost: $5/month** (flat fee for DO droplet, can change depending on server hosting)

**Latency** (time from data collection to viewing): **~200 milliseconds** (can change depending on server hosting)