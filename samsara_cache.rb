#! /usr/bin/env ruby

require 'byebug'

class Cache

  def initialize size
    @count = 0
    @head = nil
    @tail = nil
    @hash = {}
    @size = size
  end

  def get key
    if node = @hash[key]
      prev, nxt = node.prev, node.nxt
      if prev
        prev.nxt = nxt
      end
      if nxt
        nxt.prev = prev
      end
      node.prev = nil
      node.nxt = @head
      @head = node
      node.value
    end
  end

  def set key, value
    @count += 1
    node = Node.new(nil, @head, key, value)
    if @count > @size
      if @tail
        @hash.delete @tail.key
      end
      prev = @tail&.prev || node
      if prev
        prev.nxt = nil
      end
      @tail = prev
      @count -= 1
    end
    if @head
      @head.prev = node
    end
    node.nxt = @head
    @head = node
    unless @tail
      @tail = node
    end
    @hash[key] = node
    value
  end

end

class Node

  attr_accessor :prev, :nxt, :key, :value

  def initialize prev, nxt, key, value
    @prev, @nxt, @key, @value = prev, nxt, key, value
  end

end

def assert actual, expected
  if actual == expected
    puts 'passed'
  else
    puts "FAILED: actual(#{actual}) expected(#{expected})"
  end
end

cache = Cache.new 1
cache.set :key, 'value'
cache.set :key2, 'value'
assert cache.get(:key2), 'value'
assert cache.get(:key), nil

cache = Cache.new 2
cache.set :key, 'value'
cache.set :key2, 'value'
assert cache.get(:key), 'value'
