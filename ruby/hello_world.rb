#!/usr/bin/env ruby
begin
  gem 'minitest', '>= 5.0.0'
  require 'minitest/autorun'
rescue Gem::LoadError => e
  puts 'Minitest 5.0 gem must be installed for the xRuby track.'
end

class HelloWorldTest < Minitest::Test
	def test
		puts "fuck world"
		assert_equal 1,1
	end
end