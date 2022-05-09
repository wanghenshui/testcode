package main

import (
	"context"
	"fmt"
	"log"
	"time"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

// You will be using this Trainer type later in the program
type Trainer struct {
	Name string
	Age  int
	City string
	Createtime time.Time
}

func main() {
	// Set client options
	clientOptions := options.Client().ApplyURI("mongodb://localhost:27017")

	// Connect to MongoDB
	client, err := mongo.Connect(context.TODO(), clientOptions)

	if err != nil {
		log.Fatal(err)
	}

	// Check the connection
	err = client.Ping(context.TODO(), nil)

	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Connected to MongoDB!")
	collection := client.Database("test").Collection("test")
	now := time.Now()
	days := 14
	t1_time := now.AddDate(0,0,-days)
	search_date := t1_time
	t2_time := now.AddDate(0,0,-15)
	t3_time := now
	t1 := Trainer{"Ash", 10, "Pallet Town",t1_time}
	t2 := Trainer{"Misty", 10, "Cerulean City",t2_time}
	t3 := Trainer{"Brock", 15, "Pewter City",t3_time}

	filter := bson.D{
		primitive.E{Key: "createtime", Value: bson.D{primitive.E{Key: "$lt", Value: search_date},
		}},
	}
	collection.InsertOne(context.TODO(), t1)
	collection.InsertOne(context.TODO(), t2)
	collection.InsertOne(context.TODO(), t3)

	//fmt.Println(insertResult)
	var result Trainer

	err = collection.FindOne(context.TODO(), filter).Decode(&result)
	if err != nil {
		log.Println(err)
	} else {
		fmt.Println(result)
	}
	err = client.Disconnect(context.TODO())

	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("Connection to MongoDB closed.")

}
