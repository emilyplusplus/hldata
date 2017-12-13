const express = require('express')
const bodyParser = require('body-parser')
const mongoose = require('mongoose')
var cors = require('cors');

let db = mongoose.connect('mongodb://localhost/climate')

let schema = mongoose.Schema({
  temp: Number,
  lux: Number,
  time: Number
})
let Record = mongoose.model('Record', schema)

const app = express()
app.use(bodyParser.json())
app.use(cors());
app.post('/record', (req, res) => {
  res.end()

  //console.log(req)

  req.body.time = Date.now()
  new Record(req.body).save(function (err, r) {
    if (err) return console.error(err)
  })
})

app.get('/records', (req, res) => {
  Record.find({}, (err, data) => {
    //console.log(data)
    //res.end()
    res.json(data)
  })
})

app.listen(8080, '0.0.0.0')
