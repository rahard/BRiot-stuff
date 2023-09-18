const mqtt = require("mqtt");
const client = mqtt.connect("mqtt://example.domain.com");

client.on("connect", () => {
  client.subscribe("inTopic", (err) => {
    if (!err) {
      client.publish("inTopic", "Hello mqtt");
    }
  });
});

client.on("message", (topic, message) => {
  // message is Buffer
  console.log(message.toString());
  client.end();
});
