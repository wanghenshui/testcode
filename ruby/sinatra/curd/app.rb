require "sinatra"
require "data_mapper"
require "dm-serializer"
require_relative "bookmark"

DataMapper::setup(:default, "sqlite3://#{Dir.pwd}/bookmarks.db")
DataMapper.finalize.auto_upgrade!;

class Hash
	def slice(*whitelist)
		whitelist.inject({}) {|result, key| result.merge(key => self[key])}
	end
end

def get_all_bookmarks
	Bookmark.all(:order => :title)
end

get "/bookmarks" do
	content_type :json
	get_all_bookmarks.to_json
end

post "/bookmarks" do
	input = params.slice "url", "title"
	bookmark = Bookmark.create input

	[201, "/bookmarks/#{bookmark['id']}"]
end

get "/bookmarks/:id" do
	id = param[:id]
	bookmark = Bookmark.get(id)
	content_type :json
	bookmark.to_json
end
